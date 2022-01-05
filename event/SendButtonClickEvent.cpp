#include "./SendButtonClick/SendButtonClick.hpp"
#include "pcap.h"
#include "../packetsend.cpp"

SendButtonClick::SendButtonClick() {}
SendButtonClick::~SendButtonClick() {}

void SendButtonClick::sendMessage() {
    QString message = sendBar->getMessageLine()->text();
    
    int sendResult = packetSend(userName, message, true);
    
    if (sendResult == -1) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>沒有開介面你是要送個毛?</h3>", QMessageBox::Ok);
        return;
    }
}