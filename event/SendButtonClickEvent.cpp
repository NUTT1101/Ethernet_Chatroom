#include "./SendButtonClick/SendButtonClick.hpp"
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

        /* if (message.size() > 1584) {
            QMessageBox::warning(mainWindow, "warning", 
                "<h3>發送的文字上限不能超過一千五個字</h3>", QMessageBox::Ok);
            return;
        } */

        u_char packet[1500] = {'\0'};

        for (int i=0; i < 6; i++) {
			packet[i] = 0xff;
		}
        
        for (int i=6; i < 12; i++) {
            packet[i] = i + 4;
        }
		
        packet[12] = 0xff;
		packet[13] = 14; // 組別編號
		
		// 把輸入的訊息裝進封包內
        message = userName + "： " + message;
        int userNameUtf8Length = (userName + "： ").toUtf8().size();

        QByteArray messageUft8 = message.toUtf8();

        int messageLength = messageUft8.size();

        packet[14] = messageLength / 255;
        packet[15] = messageLength % 255;
        packet[16] = number / 255;
        packet[17] = number % 255;

        int packetTotalLength = messageLength + 20 + userNameUtf8Length;
        chatRoom->getChatRoom()->addItem(QVariant(packetTotalLength).toString());
        
        if (packetTotalLength > 1500) {
            int sendTimes = messageLength / 1500 + (messageLength % 1500 > 0 ? 1 : 0); 
            packet[18] = sendTimes / 255;
            packet[19] = sendTimes % 255;

            while (packetTotalLength > 0) {
                for (int i = 20; i < (packetTotalLength > 1500 ? 1500 : packetTotalLength); i++) {
                    packet[i] = (char) messageUft8.at(i - 20);
                }
                pcap_sendpacket(global_openedInterface, packet,
                    packetTotalLength > 1500 ? 1500 : packetTotalLength);
                int ruduceOneFromSendTimes = packet[18] * 255 + packet[19] - 1;  
                
                packet[18] = ruduceOneFromSendTimes / 255;
                packet[19] = ruduceOneFromSendTimes % 255;
                
                packetTotalLength -= 1480;
            }

        } else {
            for (int i = 20; i < packetTotalLength; i++) {
                packet[i] = (char) messageUft8.at(i - 20);
            }

            pcap_sendpacket(global_openedInterface, packet, packetTotalLength);
        }

        sendBar->getMessageLine()->setText("");
        chatRoom->getChatRoom()->scrollToBottom();
        number++;
    }
}