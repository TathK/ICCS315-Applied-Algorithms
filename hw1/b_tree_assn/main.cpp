#include <iostream>
#include "fc/btree.h"



void do_alot_insert(std::vector<int> vec) {
    namespace fc = frozenca;
    fc::BTreeSet<int,1<<3> btree;
    for (int i = 1; i <= 1e6; i++)
        btree.insert(vec[i]);
}

int main()
{.
    std::vector<int> vec;
    for (int i = 1; i <= 1e6; i++)
        vec.push_back(i);

    do_alot_insert(vec);

    return 0;
}
