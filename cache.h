#include "address_info.h"
#include <vector>
#pragma once
#include <map>
#include <iterator>
using namespace std;

struct cache {
    int block_size;
    int offset_size;
    int lines_in_cache;
    int number_of_sets;
    int _set_size;
    int direct_map_line_size;
    int direct_map_tag_size;
    int fully_associative_tag_size;
    int set_associative_tag_size;
    int bits_set;
    int hits;
    int misses;
    double hit_rate;
    string fifo_or_nah;
    map<string, string> direct_map;
    cache(int set_size, int size_o_cache);
    vector <address_info> addresses;
    void direct_map_cache(vector <address_info> &fileInfo);
    void fully_associative(vector <address_info> &fileInfo);
    void set_associative(vector <address_info> &fileInfo);
    double get_hit_rate();
};
