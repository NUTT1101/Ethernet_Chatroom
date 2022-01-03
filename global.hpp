#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QInputDialog>
#include <pcap.h>
#include "./widget/MainWindow.cpp"
#include "./widget/SendBar.cpp"
#include "./widget/InterfaceDropDownMenu.cpp"
#include "./widget/ChatRoom.cpp"

QString userName = "";
MainWindow *mainWindow;
SendBar *sendBar;
InterfaceDropDownMenu *menu;
ChatRoom *chatRoom;
pcap_t *global_openedInterface = nullptr;