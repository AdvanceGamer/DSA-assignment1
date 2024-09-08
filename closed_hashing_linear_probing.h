#ifndef CLOSED_HASHING_LINEAR_PROBING_H
#define CLOSED_HASHING_LINEAR_PROBING_H

#include <iostream>
#include <string>
#include <vector>
#include "metric.h"
using namespace std;

class LinearProbingHashTable
{
private:
    struct HashEntry
    {
        string key;
        bool isDeleted;

        HashEntry(const string &key = "", bool isDeleted = false)
            : key(key), isDeleted(isDeleted) {}
    };
    int tableSize;           // Number of buckets
    vector<HashEntry> table; // Vector to store entries in the hash table
    int currentSize;         // Number of elements in the table

    int hashFunction(const string &token);
    int probeFunction(int hashIndex, int i);

public:
    Metric metric;
    LinearProbingHashTable(int size);
    void insert(const string &key);
    bool search(const string &key);
    void remove(const string &key);
    void display();
};

#endif
