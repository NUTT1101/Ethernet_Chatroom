#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMap>

#include <pcap.h>

class InterfaceDropDownMenu : public QWidget {
    private:
        QGridLayout *layout = new QGridLayout;
        QGridLayout *buttonLayout = new QGridLayout(); 
        
        QComboBox *menu = new QComboBox();
        QPushButton *openButton = new QPushButton("Open");
        QPushButton *closeButton = new QPushButton("Close");
        
        QMap<QString, QString> allDevices;
        QMap<QString, QString> getAllDevices();

    public:
        InterfaceDropDownMenu(QWidget *parent);
        ~InterfaceDropDownMenu();
        void menuSetup(QComboBox *menu, QMap<QString, QString> allDevices);
        QComboBox *getInterfaceMenu();
        QPushButton *getOpenButton();
        QPushButton *getCloseButton();
        QMap<QString, QString> getAllDevicesMap();
};

InterfaceDropDownMenu::InterfaceDropDownMenu(QWidget *parent) {
    this->allDevices = this->getAllDevices();
    
    this->menu->setFixedWidth(500);
    this->menu->setFixedHeight(30);

    InterfaceDropDownMenu::menuSetup(menu, this->allDevices);

    this->openButton->setFixedWidth(100);
    this->openButton->setFixedHeight(30);

    this->closeButton->setFixedWidth(100);
    this->closeButton->setFixedHeight(30);

    this->buttonLayout->addWidget(this->openButton, 0, 0);
    this->buttonLayout->addWidget(this->closeButton, 0, 1);
    
    this->layout->addWidget(this->menu, 0, 0, Qt::AlignLeft);
    this->layout->addLayout(this->buttonLayout, 0, 1, Qt::AlignLeft);
    
    this->setLayout(this->layout);
    this->setParent(parent);
}

InterfaceDropDownMenu::~InterfaceDropDownMenu() {}

void InterfaceDropDownMenu::menuSetup(QComboBox *menu, QMap<QString, QString> allDevices) {
    int i=0;
    foreach (const auto &dev_des, allDevices.keys()) {
        menu->insertItem(++i, dev_des);
    }
}

QMap<QString, QString> InterfaceDropDownMenu::getAllDevices() {
    char errBuf[PCAP_ERRBUF_SIZE];

    pcap_if_t *allDevs;
	pcap_if_t *d;
	
	QMap<QString, QString> allDevices;
	int i=0;

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevs, errBuf) == -1) {
		allDevices.insert(QVariant("Error in pcap_findalldevs: %1").toString()
			.arg(errBuf), "");
		return allDevices;
	}

	for (d=allDevs; d; d=d->next) {
		if (d->description) {
            allDevices.insert(d->description, d->name);
        } else {
            allDevices.insert("(No description available)", "");
        }
		i++;
	}
	
	if (i == 0) {
		allDevices.clear();
		allDevices.insert("No interfaces found! Make sure Npcap is installed.", "");
		return allDevices;
	}

    pcap_freealldevs(allDevs);
	
    return allDevices;
}

QComboBox *InterfaceDropDownMenu::getInterfaceMenu() {
    return this->menu;
}

QPushButton *InterfaceDropDownMenu::getOpenButton() {
    return this->openButton;
}

QPushButton *InterfaceDropDownMenu::getCloseButton() {
    return this->closeButton;
}

QMap<QString, QString> InterfaceDropDownMenu::getAllDevicesMap() {
    return this->allDevices;
}