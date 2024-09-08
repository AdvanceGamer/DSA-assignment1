#ifndef METRIC_H
#define METRIC_H

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

class Metric
{

public:
    static int probeCount; // Tracks the probe count for the current operation
    static map<string, pair<int, int>> probeStats;
    void startProbeCounting();
    void recordProbeCount(const string &operation, bool success);
    float getAverageProbeCount(const string &operationType);
    void resetProbeCounts();
    int getProbeCount();
    void incrementProbeCount();
    const map<string, pair<int, int>> &getProbeStats();
    void printProbeStats();
};

#endif
