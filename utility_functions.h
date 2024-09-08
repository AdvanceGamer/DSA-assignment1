#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <limits>
#include <cmath>
#include <map>
using namespace std;

string adjustTokenLength(const string &token);
string decimalToTernary(int num);
int generateKey(const string &token);
void testDatastructures();
void handleUnsortedHashTable();
void handleSortedHashTable();
void handleLinearProbingHashTable();
void handleBinarySearchTree();
void inputHandling();

// void startProbeCounting();
// void recordProbeCount(const string &operation, bool success);
// float getAverageProbeCount(const string &operationType);
// void resetProbeCounts();
// int getProbeCount();
// void incrementProbeCount();
// const map<string, pair<int, int>> &getProbeStats();
// void printProbeStats();

#endif
