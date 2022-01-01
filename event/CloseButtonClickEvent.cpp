#include "./CloseButtonClick/CloseButtonClick.cpp"

CloseButtonClick::CloseButtonClick() {}
CloseButtonClick::~CloseButtonClick() {}

void CloseButtonClick::closeInterface() {
    if (global_openedInterface != nullptr) {
        pcap_close(global_openedInterface);
        global_openedInterface = nullptr;
        QMessageBox::information(mainWindow, "Information", 
            "<h3>介面監聽關閉成功!</h3>", QMessageBox::Ok);
        
    } else {
        QMessageBox::information(mainWindow, "Information",
             "<h3 style=\"color: #ad0000\">沒有被開啟的介面可以關閉!</h3>", QMessageBox::Ok);
    }
}