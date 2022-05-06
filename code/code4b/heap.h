/*********************************************
 * file:	~\code4b\heap.h                      *
 * remark:  class template for generic heaps  *
 **********************************************/
#pragma once

#include <vector>
#include <cassert>

template <class Comparable>
class Heap {
public:
    // -- CONSTRUCTORS
    // create an empty heap
    explicit Heap() : A(1) {  // slot zero is not used
    }

    // -- MEMBER FUNCTIONS

    void makeEmpty() {
        A.clear();
        A.push_back(Comparable{});
    }

    bool isEmpty() const {
        return A.size() == 1;  // slot zero is not used
    }

    void insert(const Comparable x);

    Comparable deleteMin();

private:
    // -- Private MEMBER FUNCTIONS
    void percolateUp(size_t i);
    void percolateDown(size_t i);

    // -- DATA MEMBERS
    std::vector<Comparable> A;
};

// -- MEMBER FUNCTIONS

template <class Comparable>
void Heap<Comparable>::insert(const Comparable x) {
    A.push_back(x);
    percolateUp(A.size() - 1);
}

template <class Comparable>
Comparable Heap<Comparable>::deleteMin() {
    assert(!isEmpty());

    Comparable x = A[1];
    Comparable y = A[A.size() - 1];

    A[1] = y;
    A.pop_back();
    percolateDown(1);

    return x;
}

template <class Comparable>
void Heap<Comparable>::percolateUp(size_t i) {
    Comparable x = A[i];
    auto p = i / 2;

    while (p >= 1 && A[p] > x) {
        A[i] = A[p];
        i = p;
        p = i / 2;
    }
    A[i] = x;
}

template <class Comparable>
void Heap<Comparable>::percolateDown(size_t i) {
    Comparable temp = A[i];
    auto c = 2 * i;  // left child

    while (c < A.size()) {
        if (c < A.size() - 1) {  // largest child?
            if (A[c + 1] < A[c])
                c++;
        }
        // percolate down
        if (A[c] < temp) {
            A[i] = A[c];
            i = c;
            c = 2 * i;
        } else {
            break;
        }
    }
    A[i] = temp;
}