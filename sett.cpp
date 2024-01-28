#include "sett.h"

sett::sett(address_info &addy, int _set_size, int n) {
    set_size = _set_size;
    addys.push_back(addy);
    setty = addy.set;
    addys[0].index = n;
}

bool sett::add_set_if_set_same(address_info &addy, int n, string fifo_or_nah) {

    bool is_in_set = false;

    for (int i = 0; i < addys.size(); i++) {
        if (addys[i].set_associative_tag == addy.set_associative_tag) {
            if (fifo_or_nah == "nah") {
                addys[i].index = n;
            }
            is_in_set = true;
        }
    }
    if (!is_in_set){

        if (addys.size() == set_size) {

            int lowest_index = 0;

            for (int z = 1; z < addys.size(); z++){
                if (addys[z].index < addys[lowest_index].index){
                    lowest_index = z;
                }
            }
            addys[lowest_index] = addy;
            addys[lowest_index].index = n;

        }else if (addys.size() < set_size) {
            addys.push_back(addy);
            addys[addys.size() - 1].index = n;
        }
        return false;
    }
    if(is_in_set){
        return true;
    }
}




void sett::print_set() {
    cout << setty << " ";
    for(int i = 0; i < addys.size(); i++){
        cout << addys[i].set_associative_tag  << " " << addys[i].index << " ";
    }
    cout << endl;
}