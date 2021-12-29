#include <pcap.h>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "MainWindow.cpp"
#include "./widget/SendBar.cpp"
#include "./widget/InterfaceDropDownMenu.cpp"
#include "./widget/ChatRoom.cpp"
#include <QGridLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
	
    MainWindow *mainWindow = new MainWindow();

    SendBar *sendBar = new SendBar(mainWindow);
    InterfaceDropDownMenu *menu = new InterfaceDropDownMenu(mainWindow);
    ChatRoom *chatRomm = new ChatRoom(mainWindow);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(menu, 0, 0, Qt::AlignTop);
    layout->addWidget(chatRomm, 1, 0, Qt::AlignLeft);
    layout->addWidget(sendBar, 2, 0, Qt::AlignBottom);
    mainWindow->setLayout(layout);
    
    mainWindow->show();
    return app.exec();
}