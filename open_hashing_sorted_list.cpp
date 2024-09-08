#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"
#include "metric.h"
#include <iostream>
#include <string>

using namespace std;

// ListNode constructor implementation

OpenListNode::OpenListNode(const string &k) : key(k), next(nullptr) {}

// Constructor for sortedListHashTable
sortedListHashTable::sortedListHashTable(int size) : tableSize(size)
{
    table = new OpenListNode *[tableSize]; // Allocate array of pointers
    for (int i = 0; i < tableSize; ++i)
    {
        table[i] = nullptr; // Initialize each bucket as empty
    }
}

// Destructor for sortedListHashTable

sortedListHashTable::~sortedListHashTable()
{
    // Cleanup all linked lists
    for (int i = 0; i < tableSize; ++i)
    {
        OpenListNode *entry = table[i];
        while (entry != nullptr)
        {
            OpenListNode *prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table; // Deallocate the array of pointers
}

// Hash function to calculate index for a given key
int sortedListHashTable::hashFunction(const string &token)
{
    int key = generateKey(token);
    const double goldenRatio = 0.6180339887;           // Approximation of (sqrt(5) - 1) / 2
    double product = key * goldenRatio;                // Step 1: Multiply the key by the golden ratio
    double fractionalPart = product - floor(product);  // Step 2: Extract fractional part
    int hashValue = floor(tableSize * fractionalPart); // Step 3 and 4: Multiply by m and floor the result
    return hashValue;
}

// Insert key into the hash table in sorted order
void sortedListHashTable::insert(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    OpenListNode *newNode = new OpenListNode(key);
    metric.incrementProbeCount();
    // Handle case if the bucket is empty
    if (table[hashIndex] == nullptr || table[hashIndex]->key >= key)
    {

        newNode->next = table[hashIndex];
        table[hashIndex] = newNode;
        metric.recordProbeCount("insert", true);
        return;
    }

    // Traverse the linked list to find the right position
    OpenListNode *current = table[hashIndex];
    while (current->next != nullptr && current->next->key < key)
    {
        metric.incrementProbeCount();
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    metric.recordProbeCount("insert", true);
}

// Search for a key in the hash table
// Search for a key in the table
bool sortedListHashTable::search(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    OpenListNode *entry = table[hashIndex];
    while (entry != nullptr)
    {
        metric.incrementProbeCount();
        if (entry->key == key)
        {
            // cout << key << " is found in bucket " << hashIndex << endl;
            metric.recordProbeCount("search", true);
            return true;
        }
        else if (entry->key > key)
        {
            // cout << key << " is not found Hash Table" << endl;
            metric.recordProbeCount("search", false);
            return false;
        }

        entry = entry->next;
    }
    // cout << key << " is not found Hash Table" << endl;
    metric.recordProbeCount("search", false);
    return false;
}

// Remove a key from the hash table
void sortedListHashTable::remove(const string &key)
{
    metric.startProbeCounting();
    int hashIndex = hashFunction(key);
    OpenListNode *entry = table[hashIndex];
    OpenListNode *prev = nullptr;

    // Traverse the linked list to find the key
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
        // cout << key << " found in bucket " << hashIndex << endl;
        table[hashIndex] = entry->next; // Remove the first node
    }
    else
    {
        // cout << key << " found in bucket " << hashIndex << endl;
        prev->next = entry->next; // Remove a non-first node
    }
    delete entry;
    metric.recordProbeCount("delete", true);
}

// Display the hash table
void sortedListHashTable::display()
{
    for (int i = 0; i < tableSize; ++i)
    {
        cout << "Bucket " << i << ": ";
        OpenListNode *entry = table[i];
        while (entry != nullptr)
        {
            cout << entry->key << " -> ";
            entry = entry->next;
        }
        cout << "nullptr\n";
    }
}
