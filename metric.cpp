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

int Metric::probeCount = 0;                     // Tracks the probe count for the current operation
map<string, pair<int, int>> Metric::probeStats; // Maps operation types to <totalProbes, operationCount>

// Start probe counting

void Metric::startProbeCounting()
{
    probeCount = 0; // Reset probe count at the start of the operation
}

// Record probe count for a specific operation
void Metric::recordProbeCount(const string &operation, bool success)
{
    string key;

    // Distinguish between successful and unsuccessful search operations
    if (operation == "search")
    {
        key = success ? "successful_search" : "unsuccessful_search";
    }
    else if (operation == "insert")
    {
        key = "insert";
    }
    else if (operation == "delete")
    {
        key = "delete";
    }
    else
    {
        return; // Ignore invalid operations
    }

    // Update the total probe count and operation count for the specified operation
    probeStats[key].first += probeCount;
    probeStats[key].second += 1;
}

// Get average probe count for a specific operation type
float Metric::getAverageProbeCount(const string &operationType)
{
    auto &[totalProbes, operationCount] = probeStats[operationType];
    return (operationCount == 0) ? 0 : static_cast<float>(totalProbes) / operationCount;
}

// Reset all probe counts
void Metric::resetProbeCounts()
{
    probeStats.clear();
}

// Get the current probe count
int Metric::getProbeCount()
{
    return probeCount;
}
void Metric::incrementProbeCount()
{
    probeCount++;
}

// Get probe stats (const reference to the map)
const map<string, pair<int, int>> &Metric::getProbeStats()
{
    return probeStats;
}

void Metric::printProbeStats()
{
    const auto &stats = getProbeStats(); // Retrieve probe stats

    // List of all operation types we want to track
    std::vector<std::string> operationTypes = {"successful_search", "unsuccessful_search", "insert", "delete"};

    cout << "Probe Statistics:" << endl;

    // Loop through all operations and print stats
    for (const auto &operationType : operationTypes)
    {
        // Check if the operation type exists in the stats map
        auto it = stats.find(operationType);
        int totalProbes = 0;
        int operationCount = 0;
        float averageProbes = 0.0;

        // If the operation type exists, retrieve its values
        if (it != stats.end())
        {
            totalProbes = it->second.first;
            operationCount = it->second.second;
            averageProbes = (operationCount == 0) ? 0 : static_cast<float>(totalProbes) / operationCount;
        }

        // Print the statistics for the operation
        cout << "Operation: " << operationType << endl;
        cout << "  Total Probes: " << totalProbes << endl;
        cout << "  Operation Count: " << operationCount << endl;
        cout << "  Average Probes: " << averageProbes << endl;
        cout << endl;
    }
}