#include <QApplication>
#include <QInputDialog>
#include "./widget/MainWindow.cpp"
#include "./widget/SendBar.cpp"
#include "./widget/InterfaceDropDownMenu.cpp"
#include "./widget/ChatRoom.cpp"

int number = 0;
QString userName = "";
MainWindow *mainWindow;
SendBar *sendBar;
InterfaceDropDownMenu *menu;
ChatRoom *chatRoom;
pcap_t *global_openedInterface = nullptr;