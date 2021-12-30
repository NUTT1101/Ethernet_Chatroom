#include <iostream>
#include <string>

#include <pcap.h>

int main(int argc, char **argv) {
	pcap_t *fp; // 監聽設備
	char errbuf[PCAP_ERRBUF_SIZE]; // 錯誤訊息
	u_char packet[100]; // 封包

	char* selected_device = select_device(); // 選擇要監聽的介面
	
	/* 打開要監聽的介面 */
	if ( (fp= pcap_open(selected_device,			// 監聽設備名稱
						100,				// portion of the packet to capture (only the first 100 bytes)
						PCAP_OPENFLAG_PROMISCUOUS, 	// promiscuous mode
						1000,				// 讀取最大逾時
						NULL,				// authentication on the remote machine
						errbuf				// 錯誤訊息存放
						) ) == NULL) 
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by Npcap\n", argv[1]);
		return 0;
	}

	std::cout << "opening interface successful!" << std::endl;
	
	char message[86] = {'0'}; // 訊息 (目前長度不包括 mac 以及 etherType 長度是14)
	
	while (std::cin.getline(message, 86)) {
		
		// 空輸入
		int count = 0;
		for (int i=0; i < 86; i++) {
			if ((int) message[i] == 0) {
				count++;
			}
		}
		
		if (count == 86) {
			std::cout << "what do you want to say? ";
			continue;
		}
		
		/**
		 * 前六 (index 0 ~ 5) -> 目標mac位址
		 * 第七到十二 (index 6 ~ 11) -> 發送 packet 的位址 (來源位置)
		 * 第十三 (index 12) -> 0xff (應要求)
		 */
		for (int i=0; i < 13; i++) {
			packet[i] = 0xff;
		}
		
		packet[13] = 1; // 組別編號
		
		// 把輸入的訊息裝進封包內
		for (int i = 14; i < 100; i++) {
			if (message[i - 14] != '0') {
				packet[i] = message[i - 14];
			}
		}

		// 發送封包
		if (pcap_sendpacket(fp, packet, 100) != 0) {
			fprintf(stderr,"\nError sending the packet: %s\n", pcap_geterr(fp));
			return 0;
		}

		// 把舊訊息洗掉
		for (int i=0; i < 100; i++) {
			if (i < 86) {
				message[i] = '\0';
			}
			packet[i] = '\0';
		}

		// 整理一下介面
		for (int i=0; i < 3; i++) {
			std::cout << std::endl;
		}

		std::cout << "what do you want to say? ";
	}

	return 0;
}