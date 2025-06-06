#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct PcapGlobalHeader {
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    int32_t thiszone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;
};

struct PcapPacketHeader {
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
};

int main() {
    ifstream file("test.pcap", ios::binary);
    if(!file) {
        cerr << "Error opening file\n";
        return 1;
    }

    PcapGlobalHeader gh;
    file.read(reinterpret_cast<char*>(&gh), sizeof(gh));
    if (!file) {
        cerr << "Error reading global header\n";
        return 1;
    }

    cout << "Global Header Magic Number: 0x" << hex << gh.magic_number << dec << "\n";

    int packet_num = 0;
    while(!file.eof()) {
        PcapPacketHeader ph;
        file.read(reinterpret_cast<char*>(&ph), sizeof(ph));
        if(!file) break;

        cout << "\nPacket #" << ++packet_num << ": incl_len = " << ph.incl_len << ", orig_len = " << ph.orig_len << "\n";

        vector<unsigned char> packet_data(ph.incl_len);
        file.read(reinterpret_cast<char*>(packet_data.data()), ph.incl_len);
        if(!file) {
            cout << "Incomplete packet data!\n";
            break;
        }

        // Dump first 16 bytes of the packet for example
        cout << "Packet data (first 16 bytes): ";
        for(size_t i = 0; i < min<size_t>(16, ph.incl_len); i++) {
            cout << hex << setw(2) << setfill('0') << (int)packet_data[i] << " ";
        }
        cout << dec << "\n";
    }

    file.close();
    return 0;
}
