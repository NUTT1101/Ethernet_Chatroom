#include "./CloseButtonClick/CloseButtonClick.hpp"

CloseButtonClick::CloseButtonClick() {}
CloseButtonClick::~CloseButtonClick() {}

void CloseButtonClick::closeInterface() {
    if (global_openedInterface != nullptr) {
        pcap_close(global_openedInterface);
        global_openedInterface = nullptr;
        QMessageBox::information(mainWindow, "Information", 
            "<h3>介面關閉成功!</h3>", QMessageBox::Ok);
        
    } else {
        QMessageBox::critical(mainWindow, "Information",
             "<h3>關閉失敗，尚無任何界面可被關閉!</h3>", QMessageBox::Ok);
    }
}