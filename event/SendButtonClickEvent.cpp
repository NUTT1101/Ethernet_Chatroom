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

        QByteArray messageUft8 = message.toUtf8();

        int messageLength = messageUft8.size();

        packet[14] = messageLength / 255; // 原始封包長度(不包含前20bytes)
        packet[15] = messageLength % 255; // 原始封包長度(不包含前20bytes)
        packet[16] = number / 255; // 封包序號，用於紀錄用
        packet[17] = number % 255; // 封包序號，用於紀錄用

        int packetTotalLength = messageLength + 20;

        if (packetTotalLength > 1500) {
            int currentMessage = 20;
            packet[19] = packetTotalLength / 1500; // 封包完整度，如若到0代表封包結束

            while (packetTotalLength > 0) {
                int currentLength = packetTotalLength > 1500 ? 1500 : packetTotalLength;
                for (int i = 20; i < currentLength; i++) {
                    packet[i] = (char) messageUft8.at(currentMessage++ - 20);
                }
                packet[14] = (currentLength - 20) / 255;
                packet[15] = (currentLength - 20) % 255;

                pcap_sendpacket(global_openedInterface, packet, currentLength);
                packetTotalLength -= 1480;
                packet[19] = packetTotalLength / 1500;
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