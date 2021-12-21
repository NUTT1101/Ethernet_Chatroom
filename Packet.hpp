#include <iostream>
#include <string>
#include <pcap.h>

class Packet {
    private:
        std::string message;
        u_char *packet;
        u_char mac_address[12];
        

    public:
        Packet(std::string message, u_char *packet) {
            this->message = message;
            this->packet = packet;

            for (int i=0 ; i < 12; i++) {
                this->mac_address[i] = mac_address[i];
            }
        
        }

        std::string getMessage() {
            return this->message;
        }

        u_char *getPacket() {
            return this->mac_address;
        }
};



