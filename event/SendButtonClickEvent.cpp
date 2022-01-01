#include "./SendButtonClick/SendButtonClick.cpp"
#include "pcap.h"

SendButtonClick::SendButtonClick() {}
SendButtonClick::~SendButtonClick() {}

void SendButtonClick::sendMessage() {
    QString message = sendBar->getMessageLine()->text();
    if (message != "") {
        if (global_openedInterface == nullptr) {
            QMessageBox::warning(mainWindow, "warning", 
                "<h3>沒有開介面你是要送個毛?</h3>", QMessageBox::Ok);
            return;
        }

        u_char packet[100] = {'\0'};

        for (int i=0; i < 6; i++) {
			packet[i] = 0xff;
		}
        packet[6] = 0xaa;
        packet[7] = 0xbb;
        packet[8] = 0xcc;
        packet[9] = 0xdd;
        packet[10] = 0xee;
        packet[11] = 0xff;
		
        packet[12] = 0xff;
		packet[13] = 1; // 組別編號
		
		// 把輸入的訊息裝進封包內
        QByteArray message_utf8 = message.toUtf8();
        
		for (int i = 14; i < 100; i++) {
			if (message_utf8[i - 14] != '\0') {
				packet[i] = (char) message_utf8.at(i-14);
			}
		}

        pcap_sendpacket(global_openedInterface, packet, 100);

        sendBar->getMessageLine()->setText("");
        chatRoom->getChatRoom()->scrollToBottom();
    }
}