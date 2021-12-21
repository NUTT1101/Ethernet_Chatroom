#include <iostream>
#include <string>

#include <pcap.h>

int main(int argc, char **argv) {
	pcap_t *fp; // 監聽設備
	char errbuf[PCAP_ERRBUF_SIZE]; // 錯誤訊息
	u_char packet[100]; // 封包

	if (argc != 2) {
		printf("usage: %s interface (e.g. 'rpcap://eth0')", argv[0]);
		return 0;
	}
    
	/* Open the output device */
	if ( (fp= pcap_open(argv[1],			// 監聽設備名稱
						100,				// portion of the packet to capture (only the first 100 bytes)
						PCAP_OPENFLAG_PROMISCUOUS, 	// promiscuous mode
						1000,				// 讀取最大逾時
						NULL,				// authentication on the remote machine
						errbuf				// 錯誤訊息存放
						) ) == NULL) {
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by Npcap\n", argv[1]);
		return 0;
	}

	
	std::string message;
	while (std::getline(std::cin, message)) {
		for (int i=0; i < 12; i++) {
			packet[i] = 0xff;
		}
		
		for (int i = 12; i < 100; i++) {
			if (message[i - 12] != '\0') {
				packet[i] = message[i - 12];
			}
		}

		if (pcap_sendpacket(fp, packet, 100) != 0) {
			fprintf(stderr,"\nError sending the packet: %s\n", pcap_geterr(fp));
			return 0;
		}
	}

	return 0;
}