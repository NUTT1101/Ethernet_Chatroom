#include "global.hpp"
#include <pcap.h>
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include "./event/OpenButtonClick.cpp"

OpenButtonClick::OpenButtonClick() {};
OpenButtonClick::~OpenButtonClick() {};

void OpenButtonClick::openInterface() {
    QMap<QString, QString> allDevices = menu->getAllDevicesMap();
    QString selectInterfaceDes = menu->getInterfaceMenu()->currentText();
    QString selectInterfaceName = allDevices[selectInterfaceDes];

    char open_interface[100];
    char errbuf[100];

    for (int i=0; i < 100; i++) {
        open_interface[i] = (char) selectInterfaceName.at(i).unicode();
    }
    
    /* 打開要監聽的介面 */
	this->openedInterface = pcap_open(open_interface,			// 監聽設備名稱
						100,				// portion of the packet to capture (only the first 100 bytes)
						PCAP_OPENFLAG_PROMISCUOUS, 	// promiscuous mode
						1000,				// 讀取最大逾時
						NULL,				// authentication on the remote machine
						errbuf				// 錯誤訊息存放
                        );
                        
    if (this->openedInterface != NULL) {
        QLabel *l = new QLabel("ok");
        l->setFont(QFont("Times", 10, QFont::Bold));
        l->show();
        pcap_close(this->openedInterface);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    mainWindow = new MainWindow();
    sendBar = new SendBar(mainWindow);
    menu = new InterfaceDropDownMenu(mainWindow);
    chatRoom = new ChatRoom(mainWindow);

    OpenButtonClick op;
    QObject::connect(menu->getOpenButton(), SIGNAL(clicked()), &op, SLOT(openInterface()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(menu, 0, 0, Qt::AlignTop);
    layout->addWidget(chatRoom, 1, 0, Qt::AlignLeft);
    layout->addWidget(sendBar, 2, 0, Qt::AlignBottom);
    mainWindow->setLayout(layout);
    
    mainWindow->show();
    return app.exec();
}

