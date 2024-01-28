using namespace std;
#pragma once
#include "address_info.h"
#include "cache.h"

struct sett {
    int set_size;
    vector<address_info> addys;
    string setty;
    sett(address_info &addy, int _set_size, int n);
    bool add_set_if_set_same(address_info &addy, int n, string fifo_or_nah);
    void print_set();
};



