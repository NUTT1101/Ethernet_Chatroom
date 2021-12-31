#include "./CloseButtonClick/CloseButtonClick.cpp"

CloseButtonClick::CloseButtonClick() {}
CloseButtonClick::~CloseButtonClick() {}

void CloseButtonClick::closeInterface() {
    if (global_openedInterface != nullptr) {
        pcap_close(global_openedInterface);
        global_openedInterface = nullptr;
        QMessageBox::information(mainWindow, "Information", 
            "<h3>The interface <b>Close</b> succussed!</h3>", QMessageBox::Ok);
    } else {
        QMessageBox::information(mainWindow, "Information",
             "<h3 style=\"color: #ad0000\">Not any interface was opened!</h3>", QMessageBox::Ok);
    }
}