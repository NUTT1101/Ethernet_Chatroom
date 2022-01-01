#include "ChatRoomThread.cpp"
#include <string>
#include <sstream>

ChatRoomThread::ChatRoomThread(QListWidget *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

void ChatRoomThread::run() {
    pcap_pkthdr *packet_header;
    const u_char *packet;

    while (pcap_next_ex(global_openedInterface, &packet_header, &packet) > 0) {
        std::string destinationMac = ""; // d 為 目標 mac 位址 ，s 為 來源 mac 位址
        std::string sourceMac = ""; // 來源 mac 位址
        
        // 抓出 目標以及來源 mac 位址
        for (int i=0; i < 12; i++) {
            std::stringstream byte;
            byte << std::hex << (int) packet[i];

            if (i < 6) {
                destinationMac += byte.str();   
            } else {
                sourceMac += byte.str();
            }
        }

        std::string mac = destinationMac + sourceMac;
        if (mac != "ffffffffffffaabbccddeeff") continue;
        
        std::string tmp = "";
        for (int i=14; i < 100 ; i++) {
            std::stringstream byte;

            if (packet[i] != '\0') {
                byte << (char) ((int) packet[i]);
                tmp += byte.str();
            } else {
                break;
            }
		}
        
        this->view->addItem(QString::fromStdString(tmp));
    }
    
    this->quit();
    
}
