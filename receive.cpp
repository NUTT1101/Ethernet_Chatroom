#include <iostream>
#include <string>
#include <sstream>

#include "SelectDevice.cpp"

#include <pcap.h>

int main(int argc, char **argv) {	
    pcap_t *fp; // 被打開的介面

    char errbuf[PCAP_ERRBUF_SIZE]; // 錯誤訊息存放
    int res; // pcap_open_ex 返回參數
    struct pcap_pkthdr *header; // 封包表頭
    const u_char *pkt_data; // 封封內容資料

   
	char* selected_device = select_device(); // 選擇要監聽的介面

    /* 打開要監聽的介面 */
    if ( (fp= pcap_open(selected_device,
                        100 /*snaplen*/,
                        PCAP_OPENFLAG_PROMISCUOUS /*flags*/,
                        20 /*read timeout*/,
                        NULL /* remote authentication */,
                        errbuf)
                        ) == NULL) 
    {
        fprintf(stderr,"\nError opening adapter\n");
        return -1;
    }

    // 介面整理
    for (int i=0; i < 50; i++) {
		std::cout << std::endl;
	}

	while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0) {

		if(res == 0) continue; // 連線逾時

        std::string d_and_s_mac = ""; // d 為 目標 mac 位址 ，s 為 來源 mac 位址
        std::string source_mac = ""; // 來源 mac 位址
        
        // 抓出 目標以及來源 mac 位址
        for (int j=0; j < 12; j++) {
            std::stringstream byte;
            byte << std::hex << (int) pkt_data[j];

            if (j < 6) {
                source_mac += byte.str();
            }
            
            d_and_s_mac += byte.str();
        }
		
        // 看看是不是自己的封包
        if (d_and_s_mac != "ffffffffffffffffffffffff") continue;			

        std::cout << "----------------" << std::endl;
        std::cout << "source MAC address: " << source_mac << std::endl << "message: ";

        // 印出封包內容
        for (int i=14; i < 100 ; i++) {
            std::stringstream byte;

            byte << (char) ((int) pkt_data[i]);
            
            std::cout << byte.str();
		}

		std::cout << std::endl;
		std::cout << "----------------" << std::endl;
	}

	if (res == -1) {
		fprintf(stderr, "Error reading the packets: %s\n", pcap_geterr(fp));
		return -1;
	}

	return 0;
}