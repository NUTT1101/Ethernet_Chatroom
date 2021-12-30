#include "MainWindow.cpp"
#include "./widget/SendBar.cpp"
#include "./widget/InterfaceDropDownMenu.cpp"
#include "./widget/ChatRoom.cpp"
#include <pcap.h>

MainWindow *mainWindow;
SendBar *sendBar;
InterfaceDropDownMenu *menu;
ChatRoom *chatRoom;
pcap_t *openedInterface;