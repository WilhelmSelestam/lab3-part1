#pragma once

#include <iostream>
#include <vector>
#include <cassert>

//#define TEST_PRIORITY_QUEUE

/**
 * A heap based priority queue where the root is the smallest element -- min heap
 */
template <class Comparable>
class PriorityQueue {
public:
    /**
     * Constructor to create a queue with the given capacity
     */
    explicit PriorityQueue(int initCapacity = 100);

    /**
     * Constructor to initialize a priority queue based on a given vector V
     */
    explicit PriorityQueue(const std::vector<Comparable>& V);

    // Disable copying
    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;

    /**
     * Make the queue empty
     */
    void makeEmpty();

    /**
     * Check is the queue is empty
     * Return true if the queue is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * Get the size of the queue, i.e. number of elements in the queue
     */
    size_t size() const;

    /**
     * Get the smallest element in the queue
     */
    Comparable findMin();

    /**
     * Remove and return the smallest element in the queue
     */
    Comparable deleteMin();

    /**
     * Add a new element x to the queue
     */
    void insert(const Comparable& x);

private:
    std::vector<Comparable> pq;

    // Auxiliary member functions

    /**
     * Restore the heap property
     */
    void heapify();

    /**
     * Test whether pq is a min heap
     */
    bool isMinHeap() const;

    void percolateDown(int idx);
};

/* *********************** Member functions implementation *********************** */

/**
 * Constructor to create a queue with the given capacity
 */
template <class Comparable>
PriorityQueue<Comparable>::PriorityQueue(int initCapacity) {
    /*
     * ADD CODE HERE
     */

    pq.reserve(initCapacity);
    makeEmpty();



    assert(isEmpty());  // do not remove this line
}

/**
 * Constructor to initialize a priority queue based on a given vector V
 */
template <class Comparable>
PriorityQueue<Comparable>::PriorityQueue(const std::vector<Comparable>& V) : pq{V} {
    // Implementation is provided for you
    heapify();
#ifdef TEST_PRIORITY_QUEUE
    assert(isMinHeap());
#endif
}

/**
 * Make the queue empty
 */
template <class Comparable>
void PriorityQueue<Comparable>::makeEmpty() {
    pq.clear();
    pq.push_back(Comparable{});

}

/**
 * Check is the queue is empty
 * Return true if the queue is empty, false otherwise
 */
template <class Comparable>
bool PriorityQueue<Comparable>::isEmpty() const {
    /*
     * ADD CODE HERE
     */

    //return false;  // replace this line by the correct return value

    return (pq.size() == 1);
}

/**
 * Get the size of the queue, i.e. number of elements in the queue
 */
template <class Comparable>
size_t PriorityQueue<Comparable>::size() const {
    /*
     * ADD CODE HERE
     */
    //return 0;  // replace this line by the correct return value

    return pq.size() - 1;
}

/**
 * Get the smallest element in the queue
 */
template <class Comparable>
Comparable PriorityQueue<Comparable>::findMin() {
    assert(isEmpty() == false);  // do not remove this line
    /*
     * ADD CODE HERE
     */
    //return Comparable{};  // replace this line by the correct return value

    return pq[1];
    
}

/**
 * Remove and return the smallest element in the queue
 */
template <class Comparable>
Comparable PriorityQueue<Comparable>::deleteMin() {
    assert(!isEmpty());  // do not remove this line

    /*
     * ADD CODE HERE
     */

    Comparable min = findMin();
    pq[1] = pq[pq.size() - 1];
    pq.pop_back();

    if (pq.size() > 1) {
        percolateDown(1);
    }
        
    


    // Do not remove this code block
#ifdef TEST_PRIORITY_QUEUE
    assert(isMinHeap());
#endif

    return min;  // replace this line by the correct return value
}

/**
 * Add a new element x to the queue
 */
template <class Comparable>
void PriorityQueue<Comparable>::insert(const Comparable& x) {
    /*
     * ADD CODE HERE
     */

    pq.push_back(x);

    int idx = pq.size() - 1;

    while (idx > 1) {
        int parent = (idx) / 2;
        if (pq[parent] <= pq[idx]) break;
        std::swap(pq[parent], pq[idx]);
        idx = parent;
    }


    // Do not remove this code block
#ifdef TEST_PRIORITY_QUEUE
    assert(isMinHeap());
#endif
}

/* ******************* Private member functions ********************* */

/**
 * Restore the heap property
 */
template <class Comparable>
void PriorityQueue<Comparable>::heapify() {
    assert(pq.size() > 1);  // do not remove this line

    /*
     * ADD CODE HERE
     */

    int n = pq.size() - 1;

    for (int i = n / 2; i >= 1; i--) {
        percolateDown(i);
    }
}

template <class Comparable>
void PriorityQueue<Comparable>::percolateDown(int i) {
    Comparable temp = pq[i];
    int c = 2 * i;
    int n = pq.size() - 1;

    while (c <= n) {
        if (c < n) {
            if (pq[c + 1] < pq[c]) c++;
        }
        if (pq[c] < temp) {
            pq[i] = pq[c];
            i = c;
            c = 2 * i;
        } else
            break;
    }
    pq[i] = temp;
}
/**
 * Test whether pq is a min heap
 */
template <class Comparable>
bool PriorityQueue<Comparable>::isMinHeap() const {
    /*
     * ADD CODE HERE
    */
    //return false;  // replace this line by the correct return value

    int n = pq.size() - 1;

    for (int i = 1; i < n / 2; ++i) {
        int left = 2 * i;
        int right = 2 * i + 1;
  
        if (left < n && pq[i] > pq[left]) return false;
        
        if (right < n && pq[i] > pq[right]) return false;
    }
    
    return true;
}