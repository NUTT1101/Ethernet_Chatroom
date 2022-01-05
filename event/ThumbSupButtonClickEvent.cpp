#include "./ThumbSupButtonClick/ThumbSupButtonClick.hpp"

ThumbSupButtonClick::ThumbSupButtonClick() { }
ThumbSupButtonClick::~ThumbSupButtonClick() { }

void ThumbSupButtonClick::sendThumbSup() {
    if (global_openedInterface == nullptr) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>沒有開介面你是要送個毛?</h3>", QMessageBox::Ok);
        return;
    }

    u_char packet[100] = {'\0'};

    for (int i=0; i < 6; i++) {
        packet[i] = 0xff;
    }
    
    for (int i=6; i < 12; i++) {
        packet[i] = i + 4;
    }
    
    QString message = userName + "： " + "👍";

    QByteArray messageUft8 = message.toUtf8();
    
    packet[12] = 0xff;
    packet[13] = 14; // 組別編號
    packet[14] = messageUft8.size() / 255; // 原始封包長度(不包含前20bytes)
    packet[15] = messageUft8.size() % 255; // 原始封包長度(不包含前20bytes)

    for (int i = 20; i < messageUft8.size() + 20; i++) {
        packet[i] = (char) messageUft8.at(i - 20);
    }

    pcap_sendpacket(global_openedInterface, packet, messageUft8.size() + 20);
    
    chatRoom->getChatRoom()->scrollToBottom();
}