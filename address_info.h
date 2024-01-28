using namespace std;
#pragma once
#include <iostream>

struct address_info {
public:
    string address;
    string fully_associative_tag;
    string direct_map_line;
    string direct_map_tag;
    string set_associative_tag;
    string set;
    int index;

    address_info(string &address, int &_direct_map_line_size, int &direct_map_tag_size, int &fully_associative_tag_size, int &set_associative_tag_size, int &bits_set);
};



