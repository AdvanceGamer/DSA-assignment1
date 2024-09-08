#ifndef OPEN_HASHING_SORTED_LIST_H
#define OPEN_HASHING_SORTED_LIST_H

#include <iostream>
#include <string>
#include "metric.h"
using namespace std;

struct OpenListNode
{
    string key;
    OpenListNode *next;

    OpenListNode(const string &k);
};

class sortedListHashTable
{
private:
    int tableSize;
    OpenListNode **table;
    int hashFunction(const string &token);

public:
    Metric metric;
    sortedListHashTable(int size);
    ~sortedListHashTable();
    void insert(const string &key);
    bool search(const string &key);
    void remove(const string &key);
    void display();
};

#endif
