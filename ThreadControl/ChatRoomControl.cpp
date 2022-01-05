#include "ChatRoomThread.hpp"
#include <string>
#include <sstream>
#include <QMap>

ChatRoomThread::ChatRoomThread(QListWidget *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

QMap<int, std::string> undonePacket; 
void ChatRoomThread::run() {
    pcap_pkthdr *packetHeader;
    const u_char *packet;
    int resource;
    
<<<<<<< HEAD
    while ((resource = pcap_next_ex(global_openedInterface, &packetHeader, &packet)) >= 0) {
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        std::string d_mac = "";
        for (int i=0; i < 6; i++) {
            d_mac += packet[i];
        }
=======
    QMap<int, std::string> undonePackets;
    while ((resource = pcap_next_ex(global_openedInterface, &packet_header, &packet)) >= 0) {
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        if (packet[12] != 0xff && packet[13] != 0x0e) continue;
>>>>>>> 00359a77196f90403e43efb248ca08607ad64c4a
        
        if (packet[12] != 0xff && packet[13] != 0x0e && d_mac != "ffffffffffff") continue;

        std::string message = "";
<<<<<<< HEAD
        int packetLength = packet[14] * 255 + packet[15];

        int packetNumber = packet[16] * 255 + packet[17];
        if (packet[18] == 1 && packet[19] != 0) {
            for (int i=20; i < packetLength + 20; i++) {
                std::stringstream byte;

                byte << (char) ((int) packet[i]);
                message += byte.str();
            
            }
            undonePacket[packetNumber] += message;     
            continue;
        } else if (undonePacket.value(packetNumber) != "" && packet[19] == 0){
            chatRoom->sendMessage(undonePacket[packetNumber]);
            undonePacket.remove(packetNumber);
            continue;
        }
        
        for (int i=20; i < packetLength + 20; i++) {
=======
        
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
>>>>>>> 00359a77196f90403e43efb248ca08607ad64c4a
            std::stringstream byte;

            byte << (char) ((int) packet[i]);
            message += byte.str();
		}

        chatRoom->sendMessage(message);
    }
    
    this->quit();
    
}
