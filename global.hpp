#include <QApplication>
#include <QInputDialog>
#include "./widget/MainWindow.cpp"
#include "./widget/SendBar.cpp"
#include "./widget/InterfaceDropDownMenu.cpp"
#include "./widget/ChatRoom.cpp"
#include "./SP_Neteork.cpp"

unsigned long long number = 0;
SPN_255 spn;
QString userName = "";
MainWindow *mainWindow;
SendBar *sendBar;
InterfaceDropDownMenu *menu;
ChatRoom *chatRoom;
pcap_t *global_openedInterface = nullptr;