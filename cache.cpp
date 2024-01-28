#include "cache.h"
#include "cmath"
#include <map>
#include <iterator>
#include "sett.h"

cache::cache(int set_size, int size_o_cache) {
    block_size = 64;
    _set_size = set_size;
    lines_in_cache = size_o_cache/block_size;
    number_of_sets = lines_in_cache/set_size;
    direct_map_line_size = log2(lines_in_cache);
    offset_size = log2(block_size);
    bits_set = log2(number_of_sets);
    direct_map_tag_size = 32 - direct_map_line_size - offset_size;
    fully_associative_tag_size = 32 - offset_size;
    set_associative_tag_size = 32 - bits_set - offset_size;
    hits = 0;
    misses = 0;
    hit_rate = 0.0;
}

double cache::get_hit_rate() {
    hit_rate = 100.0 * (hits / double(hits + misses));
    return hit_rate;
}

void cache::direct_map_cache(vector<address_info> &fileInfo) {
    for (int i = 0; i < fileInfo.size(); i++) {
        map<string, string>::iterator find_if_hit = direct_map.find(fileInfo[i].direct_map_line);
        if (find_if_hit != direct_map.end()) {
            if (find_if_hit->second == fileInfo[i].direct_map_tag) {
                hits++;
            } else {
                misses++;
            }
        } else {
            misses++;
        }
        direct_map[fileInfo[i].direct_map_line] = fileInfo[i].direct_map_tag;
    }
}


void cache::fully_associative(vector<address_info> &fileInfo) {
    vector<address_info> cache;
    misses = 1;
    int counter = 1;
    cache.push_back(fileInfo[0]);
    cache[0].index = 0;

    for (int y = 1; y < fileInfo.size(); y++) {
        bool is_in_cache = false;

        for (int i = 0; i < cache.size(); i++)
            if (cache[i].fully_associative_tag == fileInfo[y].fully_associative_tag) {
                hits++;
                if(fifo_or_nah == "nah")
                    cache[i].index = y;
                is_in_cache = true;
                break;
            }

        if (!is_in_cache) {
            misses++;
            if (counter == lines_in_cache) {
                int lowest_index = 0;

                for (int z = 1; z < cache.size(); z++)
                    if (cache[z].index < cache[lowest_index].index)
                        lowest_index = z;

                cache[lowest_index] = fileInfo[y];
                cache[lowest_index].index = y;

            }else if (counter < lines_in_cache) {
                cache.push_back(fileInfo[y]);
                cache[counter].index = y;
                counter++;
            }
        }
    }
}

void cache::set_associative(vector<address_info> &fileInfo) {
    vector<sett> cache;

    sett set1(fileInfo[0], _set_size, 0);
    set1.setty = fileInfo[0].set;
    cache.push_back(set1);
    misses = 1;

    int counter = 1;
    bool is_a_hit = false;
    bool is_it_a_set = false;

    for (int y = 1; y < fileInfo.size(); y++) {

        for (int i = 0; i < cache.size(); i++) {

            if (cache[i].setty == fileInfo[y].set) {
                is_a_hit = cache[i].add_set_if_set_same(fileInfo[y], y, fifo_or_nah);
                is_it_a_set = true;
                break;
            }
        }
        if (is_a_hit) {
            hits++;

        } else {
            misses++;
            if(!is_it_a_set){
                cache.emplace_back(fileInfo[y], _set_size, y);
                fileInfo[y].index = y;
                cache[counter].setty = fileInfo[y].set;
                counter++;
            }
        }
        is_it_a_set = false;
        is_a_hit = false;
    }
}