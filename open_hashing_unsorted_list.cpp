#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"
#include "metric.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

// ListNode constructor
unsortedListHashTable::ListNode::ListNode(const string &k) : key(k), next(nullptr) {}

int unsortedListHashTable::hashFunction(const string &token)
{
    int key = generateKey(token);
    const double goldenRatio = 0.6180339887;           // Approximation of (sqrt(5) - 1) / 2
    double product = key * goldenRatio;                // Step 1: Multiply the key by the golden ratio
    double fractionalPart = product - floor(product);  // Step 2: Extract fractional part
    int hashValue = floor(tableSize * fractionalPart); // Step 3 and 4: Multiply by m and floor the result
    return hashValue;
}

// Constructor for unsortedListHashTable
unsortedListHashTable::unsortedListHashTable(int size) : tableSize(size)
{
    table = new ListNode *[tableSize]; // Allocate array of pointers
    for (int i = 0; i < tableSize; ++i)
    {
        table[i] = nullptr; // Initialize each bucket as empty
    }
    // table.resize(size, nullptr);
}

// Destructor for unsortedListHashTable
unsortedListHashTable::~unsortedListHashTable()
{
    // Cleanup all linked lists
    for (int i = 0; i < tableSize; ++i)
    {
        ListNode *entry = table[i];
        while (entry != nullptr)
        {
            ListNode *prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table; // Deallocate the array of pointers
}

// Hash function to calculate index for a given key

// Insert key into the hash table
void unsortedListHashTable::insert(const string &key)
{
    metric.startProbeCounting();
    metric.incrementProbeCount();
    int hashIndex = hashFunction(key);
    ListNode *newNode = new ListNode(key);
    newNode->next = table[hashIndex];
    table[hashIndex] = newNode;
    metric.recordProbeCount("insert", true);
}

// Search for a key in the hash table
bool unsortedListHashTable::search(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    ListNode *entry = table[hashIndex];
    while (entry != nullptr)
    {
        metric.incrementProbeCount();
        if (entry->key == key)
        {
            // cout << key << " is found in bucket" << hashIndex << endl;
            metric.recordProbeCount("search", true);
            return true;
        }
        entry = entry->next;
    }
    metric.recordProbeCount("search", false);
    return false;
}

// Remove a key from the hash table
void unsortedListHashTable::remove(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    ListNode *entry = table[hashIndex];
    ListNode *prev = nullptr;

    while (entry != nullptr && entry->key != key)
    {
        metric.incrementProbeCount();
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr)
    {
        // cout << key << " not found" << endl;
        metric.recordProbeCount("delete", false);
        return; // Key not found
    }

    if (prev == nullptr)
    {
        // cout << key << " found in bucket" << hashIndex << endl;
        table[hashIndex] = entry->next; // Remove the first node
    }
    else
    {
        // cout << key << " found in bucket" << hashIndex << endl;
        prev->next = entry->next; // Remove a non-first node
    }
    delete entry;
    metric.recordProbeCount("delete", true);
}
// Display the hash table
void unsortedListHashTable::display()
{
    for (int i = 0; i < tableSize; ++i)
    {
        cout << "Bucket " << i << ": ";
        ListNode *entry = table[i];
        while (entry != nullptr)
        {
            cout << entry->key << " -> ";
            entry = entry->next;
        }
        cout << "nullptr\n";
    }
}
