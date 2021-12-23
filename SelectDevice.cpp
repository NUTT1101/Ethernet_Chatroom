#include <pcap.h>
#include <iostream>

#include "SelectDevice.hpp"

char error = -1;

char *select_device() {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_if_t *alldevs;
	pcap_if_t *d;
	
	int inum;
	int i=0;
	pcap_t *adhandle;

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	for (d=alldevs; d; d=d->next) {
		std::cout << ++i << ". "  << d->name << std::endl; 
		
		if (d->description) {
            std::cout << d->description << std::endl;
        } else {
            std::cout << "(No description available)" << std::endl;
        }
	}
	
	if (i == 0) {
		printf("\nNo interfaces found! Make sure Npcap is installed.\n");
        return &error;
    }
	
	//open interface number.
	printf("Enter the interface number (1-%d):",i);
	std::cin >> inum;
	
	if (inum < 1 || inum > i) {
		std::cout << std::endl << "Interface number out of range." << std::endl;
		pcap_freealldevs(alldevs);
        return &error;
	}
	
	/* Jump to the selected adapter */
	for (d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

    pcap_freealldevs(alldevs);
	
    return d->name;
}
