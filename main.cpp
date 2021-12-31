#include "global.hpp"
#include "./event/OpenButtonClickEvent.cpp"
#include "./event/CloseButtonClickEvent.cpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    mainWindow = new MainWindow();
    sendBar = new SendBar(mainWindow);
    menu = new InterfaceDropDownMenu(mainWindow);
    chatRoom = new ChatRoom(mainWindow);

    OpenButtonClick openButton;
    CloseButtonClick closeButton;
    QObject::connect(menu->getOpenButton(), SIGNAL(clicked()), &openButton, SLOT(openInterface()));
    QObject::connect(menu->getCloseButton(), SIGNAL(clicked()), &closeButton, SLOT(closeInterface()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(menu, 0, 0, Qt::AlignTop);
    layout->addWidget(chatRoom, 1, 0, Qt::AlignLeft);
    layout->addWidget(sendBar, 2, 0, Qt::AlignBottom);
    mainWindow->setLayout(layout);
    
    mainWindow->show();
    return app.exec();
}

