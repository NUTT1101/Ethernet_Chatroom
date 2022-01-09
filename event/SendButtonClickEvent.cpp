#include "./SendButtonClick/SendButtonClick.hpp"
#include "../packetsend.cpp"

SendButtonClick::SendButtonClick() {}
SendButtonClick::~SendButtonClick() {}

void SendButtonClick::sendMessage() {
    QString message = sendBar->getMessageLine()->text();
    if (message.toUtf8().size() > 2000) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>發送的文字應小於2000個</h3>", QMessageBox::Ok);
        return;
    }
    
    int sendResult = packetSend(userName, message, true);
    
    if (sendResult == -1) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>沒有開介面你是要送個毛?</h3>", QMessageBox::Ok);
        return;
    }
}