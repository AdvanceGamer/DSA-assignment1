#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"
#include "metric.h"
#include <iostream>
#include <string>
using namespace std;

// LinearProbingHashTable::HashEntry::HashEntry(const string &key = "", bool isDeleted = false)
//     : key(key), isDeleted(isDeleted) {}
int LinearProbingHashTable::hashFunction(const string &token)
{
    int key = generateKey(token);
    const double goldenRatio = 0.6180339887;           // Approximation of (sqrt(5) - 1) / 2
    double product = key * goldenRatio;                // Step 1: Multiply the key by the golden ratio
    double fractionalPart = product - floor(product);  // Step 2: Extract fractional part
    int hashValue = floor(tableSize * fractionalPart); // Step 3 and 4: Multiply by m and floor the result
    return hashValue;
}

int LinearProbingHashTable::probeFunction(int hashIndex, int i)
{
    return (hashIndex + i) % tableSize;
}

LinearProbingHashTable::LinearProbingHashTable(int size) : tableSize(size), currentSize(0)
{
    table.resize(tableSize); // Initialize table with empty entries
}

void LinearProbingHashTable::insert(const string &key)
{
    metric.startProbeCounting();
    if (currentSize == tableSize)
    {
        metric.incrementProbeCount();
        // cout << "Hash table is full" << endl;
        metric.recordProbeCount("insert", false);
        return;
    }

    int hashIndex = hashFunction(key);
    int i = 0;

    // Linear probing until we find an empty slot or a deleted slot
    while (!table[probeFunction(hashIndex, i)].key.empty() && !table[probeFunction(hashIndex, i)].isDeleted)
    {
        metric.incrementProbeCount();
        i++;
    }

    // Insert the key at the found position
    table[probeFunction(hashIndex, i)] = HashEntry(key);
    currentSize++;
    metric.recordProbeCount("insert", true);
}

bool LinearProbingHashTable::search(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    int i = 0;

    // Linear probing to search for the key
    while (!table[probeFunction(hashIndex, i)].key.empty() && i < tableSize)
    {
        metric.incrementProbeCount();
        if (table[probeFunction(hashIndex, i)].key == key && !table[probeFunction(hashIndex, i)].isDeleted)
        {
            // cout << key << " found at index " << probeFunction(hashIndex, i) << endl;
            metric.recordProbeCount("search", true);
            return true;
        }
        i++;
    }

    // cout << key << " not found" << endl;
    metric.recordProbeCount("search", false);
    return false;
}

void LinearProbingHashTable::remove(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    int i = 0;

    // Linear probing to find the key to delete
    while (!table[probeFunction(hashIndex, i)].key.empty() && i < tableSize)
    {
        metric.incrementProbeCount();
        if (table[probeFunction(hashIndex, i)].key == key && !table[probeFunction(hashIndex, i)].isDeleted)
        {
            table[probeFunction(hashIndex, i)].isDeleted = true; // Mark the slot as deleted
            currentSize--;
            // cout << key << " deleted from index " << probeFunction(hashIndex, i) << endl;
            metric.recordProbeCount("delete", true);
            return;
        }
        i++;
    }

    // cout << key << " not found for deletion" << endl;
    metric.recordProbeCount("delete", false);
}

void LinearProbingHashTable::display()
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (!table[i].key.empty() && !table[i].isDeleted)
        {
            cout << "Index " << i << ": " << table[i].key << endl;
        }
        else
        {
            cout << "Index " << i << ": empty" << endl;
        }
    }
}
