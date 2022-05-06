/*********************************************
 * file:	~\code4b\dsets.cpp                *
 * remark: implementation of disjoint sets    *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

#include "dsets.h"

// -- CONSTRUCTORS

DSets::DSets(size_t theSize) : V(theSize + 1) {  // slot zero is not used
    assert(theSize > 0);
    init();
}

// -- MEMBER FUNCTIONS

// create initial sets
void DSets::init() {
    for (size_t i = 1; i < V.size(); ++i) {
        V[i] = -1;  // every disjoint set has one node -- singleton
    }
}

// join sets named r and s where r != s
// i.e. join trees with roots r and s
void DSets::join(int r, int s) {
    assert(r != s);
    assert(r >= 1 && r <= V.size() - 1);
    assert(s >= 1 && s <= V.size() - 1);
    assert(V[r] < 0);
    assert(V[s] < 0);

    // simple union
    V[r] = s;

    // *** TODO ***
    // Do Union by Size
}

// return name of current set for x
// i.e. return root of tree for x
int DSets::find(int x) {
    assert(x >= 1 && x <= V.size() - 1);

   // simple find
    if (V[x] < 0) {
        return x;
    } else {
        return find(V[x]);
    }

    // *** TODO ***
    // find with path compression
}

// just in case ...
void DSets::print() const {
    std::cout << "\n";

    for (size_t i = 1; i < V.size(); i++) {
        std::cout << std::setw(4) << i;
    }
    std::cout << "\n";

    for (size_t i = 1; i < V.size(); i++) {
        std::cout << std::setw(4) << V[i];
    }
    std::cout << "\n";
}
