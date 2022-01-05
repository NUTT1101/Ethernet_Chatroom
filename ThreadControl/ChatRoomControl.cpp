#include "ChatRoomThread.hpp"

ChatRoomThread::ChatRoomThread(QTextBrowser *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

QMap<int, std::string> undonePacket; 
void ChatRoomThread::run() {
    pcap_pkthdr *packetHeader;
    const u_char *packet;
    int resource;
    
    while ((resource = pcap_next_ex(global_openedInterface, &packetHeader, &packet)) >= 0) {
        if (!chatRoom->getChatRoom()->verticalScrollBar()->isSliderDown()) {
            chatRoom->getChatRoom()->verticalScrollBar()->setValue(
                chatRoom->getChatRoom()->verticalScrollBar()->maximum());
        }
        
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        std::string d_mac = "";
        for (int i=0; i < 6; i++) {
            d_mac += packet[i];
        }
        
        if (packet[12] != 0xff && packet[13] != 0x0e && d_mac != "ffffffffffff") continue;

        std::string message = "";
        int packetLength = packet[14] * 255 + packet[15];
        int packetNumber = packet[16], packetTick = packet[17] * 255 + packet[18];
        if (packet[19] == 1 && packetTick != 0) {
            for (int i=20; i < packetLength + 20; i++) {
                std::stringstream byte;

                byte << (char) ((int) packet[i]);
                message += byte.str();
            }

            undonePacket[packetNumber] += message;     
            continue;
        } else if (undonePacket.value(packetNumber) != "" && packetTick == 0){
            chatRoom->sendMessage(undonePacket[packetNumber]);
            undonePacket.remove(packetNumber);
            continue;
        }
        
        for (int i=20; i < packetLength + 20; i++) {
            std::stringstream byte;

            byte << (char) ((int) packet[i]);
            message += byte.str();
		}

        chatRoom->sendMessage(message);
        
    }
    
    this->quit();
}
