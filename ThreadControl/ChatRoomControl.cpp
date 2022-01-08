#include "ChatRoomThread.hpp"
#include <QDir>
#include <QTextBlock>

ChatRoomThread::ChatRoomThread(QTextBrowser *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

QMap<int, std::string> undonePacket;
QMap<int, QByteArray> undonePhotos;

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
        int packetLength = packet[14] * 256 + packet[15];
        int packetNumber = packet[16] * 256 + packet[17];
        
        if (packet[19] == 1) {
            for (int i=20; i < (packetHeader->caplen + 20 > 1500 ? 1500 : packetHeader->caplen); i++) {
                undonePhotos[packetNumber].append(packet[i]);
            }
            
            if (packet[18] != 1) continue;
            if (packet[18] == 1) {
                QDir temp("received");
                if (!QDir("received").exists()) {
                    temp.mkdir(".");
                }
                
                QString fileName, fileEx, sendUser;
                int j;
                for (j=0; j < undonePhotos[packetNumber].size(); j++) {
                    if (undonePhotos[packetNumber].at(j) != '\0') {
                        fileName += QString(undonePhotos[packetNumber].at(j)); 
                    } else break;
                }

                for (++j; j < undonePhotos[packetNumber].size(); j++) {
                    if (undonePhotos[packetNumber].at(j) != '\0') {
                        fileEx += QString(undonePhotos[packetNumber].at(j));
                    } else break;
                }
                
                std::string user;
                for (++j; j < undonePhotos[packetNumber].size(); j++) {
                    if (undonePhotos[packetNumber].at(j) != '\0') {
                        std::stringstream byte;
                        byte << (char) undonePhotos[packetNumber].at(j);
                        user += byte.str();
                    } else break;
                }
                sendUser = QString::fromStdString(user);

                QByteArray fileData;
                for (int i = j + 1; i < undonePhotos[packetNumber].size(); i++) {
                    fileData.append(undonePhotos[packetNumber].at(i));
                }

                QFile file("./received/" + fileName + "." + fileEx);
                file.open(QIODevice::WriteOnly);
                file.write(fileData);
                file.close();    
                undonePhotos.remove(packetNumber);
                chatRoom->getChatRoom()->
                    insertHtml("<br><a style=\"color: red;\">您收到來自 " + sendUser + "的檔案" + fileName + "." + fileEx + "</a>");
                continue;
            }
        
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

