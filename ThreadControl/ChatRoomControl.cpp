#include "ChatRoomThread.hpp"
#include <string>
#include <sstream>
#include <ctime>

ChatRoomThread::ChatRoomThread(QListWidget *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

void ChatRoomThread::run() {
    pcap_pkthdr *packet_header;
    const u_char *packet;
    int resource;
    
    while ((resource = pcap_next_ex(global_openedInterface, &packet_header, &packet)) >= 0) {
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        if (packet[12] != 0xff && packet[13] != 0x01) continue;
        
        std::string message = "";
        int packet_length = packet[14] * 255 + packet[15];
        
        for (int i=16; i < packet_length + 16; i++) {
            std::stringstream byte;

            byte << (char) ((int) packet[i]);
            message += byte.str();
		}

        chatRoom->getChatRoom()->scrollToBottom();
        this->view->addItem(QString::fromStdString(message));
    }
    
    this->quit();
    
}
