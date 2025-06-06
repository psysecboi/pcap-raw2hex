#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
    ifstream file("test3.pcap", ios::binary);

    if(!file){
        cerr<<"Error: Could not open the file.\n";
        return 1;
    }

    vector<unsigned char> buffer;
    unsigned char byte;

    while(file.read(reinterpret_cast<char*>(&byte), 1)) {
        buffer.push_back(byte);
    }

    for(auto it : buffer){
        cout<<dec<<static_cast<int>(it)<<" ";
    }
    cout<<"\n\n\n";

    for(auto it : buffer){
        cout<<hex<<setw(2)<<setfill('0')<<static_cast<int>(it)<< " ";
    }

    file.close();
    return 0;
}
