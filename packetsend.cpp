int packetSend(QString userName, QString message, bool clearMessageLine) {
    if (global_openedInterface == nullptr) {
        return -1;
    }
    
    if (message != "") {        
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

        packet[14] = messageLength / 256; // 原始封包長度(不包含前20bytes)
        packet[15] = messageLength % 256; // 原始封包長度(不包含前20bytes)
        packet[16] = number / 256; // 封包編號，用於紀錄用
        packet[17] = number % 256; // 封包編號，用於紀錄用
        packet[19] = 0;

        int packetTotalLength = messageLength + 20;

        if (packetTotalLength > 1500) {
            int currentMessage = 20;

            while (packetTotalLength > 0) {
                int currentLength = packetTotalLength > 1500 ? 1500 : packetTotalLength;
                for (int i = 20; i < currentLength; i++) {
                    packet[i] = (char) messageUft8.at(currentMessage++ - 20);
                }
                packet[14] = (currentLength - 20) / 256;
                packet[15] = (currentLength - 20) % 256;
                
                packet_encryption(packet, spn, currentLength);
                pcap_sendpacket(global_openedInterface, packet, currentLength);
                packetTotalLength -= 1480;
            }
            
        } else {
            for (int i = 20; i < packetTotalLength; i++) {
                packet[i] = (char) messageUft8.at(i - 20);
            }

            packet_encryption(packet, spn, packetTotalLength);
            pcap_sendpacket(global_openedInterface, packet, packetTotalLength);
        }        

        if (clearMessageLine) {
            sendBar->getMessageLine()->setText("");
        }
        
        chatRoom->getChatRoom()->verticalScrollBar()->setValue(
            chatRoom->getChatRoom()->verticalScrollBar()->maximum());
        number++;
    }

    return 0;
}