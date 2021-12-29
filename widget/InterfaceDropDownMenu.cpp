#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#include <QString>
#include <QMap>

#include "./npcap/getAllDevices.cpp"

class InterfaceDropDownMenu : public QWidget {
    private:
        QGridLayout *layout = new QGridLayout;
        QComboBox *menu = new QComboBox();
        QGridLayout *buttonLayout = new QGridLayout();
        QPushButton *openButton = new QPushButton("Open");
        QPushButton *closeButton = new QPushButton("Close");

    public:
        InterfaceDropDownMenu(QWidget *parent) {
            this->menu->setFixedWidth(500);
            this->menu->setFixedHeight(30);
            InterfaceDropDownMenu::menuSetup(menu);

            this->openButton->setFixedWidth(100);
            this->openButton->setFixedHeight(30);

            this->closeButton->setFixedWidth(100);
            this->closeButton->setFixedHeight(30);

            this->buttonLayout->addWidget(openButton, 0, 0);
            this->buttonLayout->addWidget(closeButton, 0, 1);
            
            this->layout->addWidget(menu, 0, 0, Qt::AlignLeft);
            this->layout->addLayout(buttonLayout, 0, 1, Qt::AlignLeft);
            
            this->setLayout(layout);
            this->setParent(parent);
        }

        void menuSetup(QComboBox *menu) {
            QMap<QString, QString> allDevices = getAllDevices();
            
            int i=0;
            foreach (const auto &dev_des, allDevices.keys()) {
                menu->insertItem(++i, QIcon("chat.jpg"), dev_des);
            }
        }
};