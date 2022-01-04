#include "ChatRoomThread.hpp"
#include <string>
#include <sstream>
#include <QMap>

ChatRoomThread::ChatRoomThread(QListWidget *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

void ChatRoomThread::run() {
    pcap_pkthdr *packet_header;
    const u_char *packet;
    int resource;
    
    QMap<int, std::string> undonePackets;
    while ((resource = pcap_next_ex(global_openedInterface, &packet_header, &packet)) >= 0) {
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        if (packet[12] != 0xff && packet[13] != 0x0e) continue;
        
        std::string message = "";
        
        /* int colonIndex;
        for (int i=0; i < packet_header->caplen; i++) {
            if (packet[i] == 0xbc && packet[i+1] == 0x9a && packet[i+2] == 0x20) {
                colonIndex = i+2;
                break;
            }
        }

        std::string sender;
        for (int i=20; i <= colonIndex; i++) {
            std::stringstream byte;

            byte << (char) ((int) packet[i]);
            sender += byte.str();
        } 
        
        int packetIsComplete = packet[18] * 255 + packet[19];
        int packetNumber = packet[16] * 255 + packet[17];
        
        if (packetIsComplete > 0) {
            if (!undonePackets.contains(packetNumber)) {
                for (int i=colonIndex + 1; i < packet_header->caplen; i++) {
                    std::stringstream byte;

                    byte << (char) ((int) packet[i]);
                    message += byte.str();
                }

                this->view->addItem(QString::fromStdString(sender + message));
                undonePackets[packetNumber] += sender + message;
            } else {
                for (int i=colonIndex + 1; i < packet_header->caplen; i++) {
                    std::stringstream byte;

                    byte << (char) ((int) packet[i]);
                    message += byte.str();
                }
                this->view->addItem(QString::fromStdString(message));
                undonePackets[packetNumber] += message;
            }

            if (packetIsComplete == 1) {
                undonePackets.remove(undonePackets.key(undonePackets[packetNumber]));
            }

            continue;
        } */
        
        for (int i=20; i < packet_header->caplen; i++) {
            std::stringstream byte;

            byte << (char) ((int) packet[i]);
            message += byte.str();
		}

        chatRoom->getChatRoom()->scrollToBottom();
        this->view->addItem(QString::fromStdString(message));
    }
    
    this->quit();
    
}
