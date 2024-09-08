#ifndef OPEN_HASHING_UNSORTED_LIST_H
#define OPEN_HASHING_UNSORTED_LIST_H

#include <iostream>
#include <string>
#include "metric.h"
using namespace std;

class unsortedListHashTable
{
private:
    struct ListNode
    {
        string key;
        ListNode *next;

        ListNode(const string &k);
    };

    int tableSize;
    ListNode **table;
    // vector<ListNode *>table;
    int hashFunction(const string &token);

public:
    Metric metric;
    unsortedListHashTable(int size);
    ~unsortedListHashTable();
    void insert(const string &key);
    bool search(const string &key);
    void remove(const string &key);
    void display();
};

#endif
