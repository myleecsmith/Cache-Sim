using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "address_info.h"
#include "cache.h"
#include "sett.h"

void readFile(string fileName, vector <address_info> &fileInfo, int direct_map_line_size, int direct_map_tag_size, int fully_associative_tag_size, int set_associative_tag_size, int bits_set);

int main() {

    vector <address_info> addresses;
//test 2048, 4096, 8192

    cache _cache(2, 2048);
    readFile("swim.trace", addresses, _cache.direct_map_line_size, _cache.direct_map_tag_size, _cache.fully_associative_tag_size, _cache.set_associative_tag_size, _cache.bits_set);
    _cache.fifo_or_nah = "yah";
    _cache.fully_associative(addresses);
    cout << "hit rate is: " << _cache.get_hit_rate() << endl;
    cout << "total hits: " << _cache.hits << endl;
    cout << "total misses: " << _cache.misses << endl;

    return 0;
}

void readFile(string fileName, vector <address_info> &fileInfo, int direct_map_line_size, int direct_map_tag_size, int fully_associative_tag_size, int set_associative_tag_size, int bits_set){
    ifstream openFile(fileName);
    if(openFile.is_open()){

        string line_of_file;
        while(getline(openFile, line_of_file)){
            istringstream line(line_of_file);

            string useless;
            getline(line, useless, 'x');
            string address;
            getline(line,address, ' ');
            fileInfo.push_back(address_info(address, direct_map_line_size, direct_map_tag_size, fully_associative_tag_size, set_associative_tag_size, bits_set));
        }
        openFile.close();
    }
}
