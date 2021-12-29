#include <pcap.h>
#include <QStringList>
#include <QMap>
#include <QString>
#include <QVariant>

char error = -1;

QMap<QString, QString> getAllDevices() {
    char errBuf[PCAP_ERRBUF_SIZE];

    pcap_if_t *allDevs;
	pcap_if_t *d;
	
	QMap<QString, QString> allDevices;
	int i=0;

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevs, errBuf) == -1) {
		allDevices.insert(QVariant("Error in pcap_findalldevs: %1").toString()
			.arg(errBuf), "");
		return allDevices;
	}

	for (d=allDevs; d; d=d->next) {
		if (d->description) {
            allDevices.insert(d->description, d->name);
        } else {
            allDevices.insert("(No description available)", "");
        }
		i++;
	}
	
	if (i == 0) {
		allDevices.clear();
		allDevices.insert("No interfaces found! Make sure Npcap is installed.", "");
		return allDevices;
	}

    pcap_freealldevs(allDevs);
	
    return allDevices;
}
