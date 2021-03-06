#include "ChatRoomThread.hpp"

ChatRoomThread::ChatRoomThread(QTextBrowser *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

QMap<int, std::string> undonePacket;
QMap<int, QByteArray> undoneFiles;

void ChatRoomThread::run() {
    pcap_pkthdr *packetHeader;
    u_char *packet;
    int resource;
    
    while ((resource = pcap_next_ex(global_openedInterface, &packetHeader, &packet)) >= 0) {
        if (global_openedInterface == nullptr) break;
        if (resource == 0) continue;
        
        std::string d_mac = "";
        for (int i=0; i < 6; i++) {
            d_mac += packet[i];
        }
        
        if (packet[12] != 0xff && packet[13] != 0x0e && d_mac != "ffffffffffff") continue;

        std::string message = "";
        
        if (packet[19] == 0) packet_decrypt(packet, spn, packetHeader->caplen);

        int packetNumber = packet[16] * 256 + packet[17];
        
        if (packet[19] == 1 || packet[19] == 2) {
            for (unsigned int i=20; i < (packetHeader->caplen == 1500 ? 1500 : packetHeader->caplen); i++) {
                undoneFiles[packetNumber].append(packet[i]);
            }
            
            if (packet[18] == 1) {
                QDir temp("received");
                if (!QDir("received").exists()) {
                    temp.mkdir(".");
                }
                
                QString fileName, fileEx, sendUser;
                int index;
                for (index=0; index < undoneFiles[packetNumber].size(); index++) {
                    if (undoneFiles[packetNumber].at(index) != '\0') {
                        fileName += QString(undoneFiles[packetNumber].at(index)); 
                    } else break;
                }

                for (++index; index < undoneFiles[packetNumber].size(); index++) {
                    if (undoneFiles[packetNumber].at(index) != '\0') {
                        fileEx += QString(undoneFiles[packetNumber].at(index));
                    } else break;
                }
                
                std::string user;
                for (++index; index < undoneFiles[packetNumber].size(); index++) {
                    if (undoneFiles[packetNumber].at(index) != '\0') {
                        std::stringstream byte;
                        byte << (char) undoneFiles[packetNumber].at(index);
                        user += byte.str();
                    } else break;
                }
                sendUser = QString::fromStdString(user);

                QByteArray fileData;
                for (int i = index + 1; i < undoneFiles[packetNumber].size(); i++) {
                    fileData.append(undoneFiles[packetNumber].at(i));
                }
                undoneFiles.remove(packetNumber);

                QString fileFullName = fileName + "." + fileEx;
                QFile file("./received/" + fileFullName);
                int fileNumber = 1;
                while (file.exists()) {
                    fileFullName = fileName + "(" + QVariant(fileNumber++).toString() + ")." + fileEx;
                    file.setFileName("./received/" + fileFullName);
                }

                file.open(QIODevice::WriteOnly);
                file.write(fileData);
                
                if (packet[19] == 2) {
                    chatRoom->getChatRoom()->append(sendUser + "???");
                    chatRoom->getChatRoom()->
                        append("<div><img src=\"./received/" + fileFullName + "\" width=\"768\" height=\"432\"></div>");
                    file.remove();

                } else if (sendUser != userName) {
                    chatRoom->getChatRoom()->
                        append("<div><a style=\"color: red;\">???????????????" + sendUser + "?????????" + fileFullName + "</a></div>");
                }
                file.close();
            }
            chatRoom->getChatRoom()->verticalScrollBar()->setValue(
                chatRoom->getChatRoom()->verticalScrollBar()->maximum());
            
            continue;
        }
        
        
        for (unsigned int i=20; i < packetHeader->caplen; i++) {
            std::stringstream byte;
            byte << (char) packet[i];
            
            message += byte.str();
		}

        chatRoom->sendMessage(message);
        chatRoom->getChatRoom()->verticalScrollBar()->setValue(
                chatRoom->getChatRoom()->verticalScrollBar()->maximum());
    }
    
    this->quit();
}

