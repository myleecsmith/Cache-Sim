#include "address_info.h"
using namespace std;
#include <string>
address_info::address_info(string &address, int &_direct_map_line_size, int &direct_map_tag_size, int &fully_associative_tag_size, int &set_associative_tag_size,int &bits_set) {

    string address_bin = "";
    for (int i = 0; i < address.length (); ++i)
    {
        switch (address [i])
        {
            case '0': address_bin.append ("0000"); break;
            case '1': address_bin.append ("0001"); break;
            case '2': address_bin.append ("0010"); break;
            case '3': address_bin.append ("0011"); break;
            case '4': address_bin.append ("0100"); break;
            case '5': address_bin.append ("0101"); break;
            case '6': address_bin.append ("0110"); break;
            case '7': address_bin.append ("0111"); break;
            case '8': address_bin.append ("1000"); break;
            case '9': address_bin.append ("1001"); break;
            case 'A':
            case 'a':
                address_bin.append ("1010"); break;
            case 'B':
            case 'b':
                address_bin.append ("1011"); break;
            case 'C':
            case 'c':
                address_bin.append ("1100"); break;
            case 'D':
            case 'd':
                address_bin.append ("1101"); break;
            case 'E':
            case 'e':
                address_bin.append ("1110"); break;
            case 'F':
            case 'f':
                address_bin.append ("1111"); break;
        }
    }
    address = address_bin;
    direct_map_line = address.substr(direct_map_tag_size, direct_map_tag_size);
    direct_map_tag = address.substr(0, direct_map_tag_size);
    fully_associative_tag = address.substr(0, fully_associative_tag_size);
    set_associative_tag = address.substr(0, set_associative_tag_size);
    set = address.substr(set_associative_tag_size, bits_set);
    index = 0;
}
