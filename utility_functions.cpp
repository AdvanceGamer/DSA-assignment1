#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

string adjustTokenLength(const string &token)
{
    if (token.length() < 10)
    {
        return token + string(10 - token.length(), '*'); // Pad with '*'
    }
    else if (token.length() > 10)
    {
        return token.substr(0, 10); // Truncate to first 10 characters
    }
    return token; // If already 10 characters, return as is
}

int generateKey(const string &token)
{
    int key = 0;
    for (char ch : token)
    {
        key += int(ch); // Add the ASCII value of each character
    }
    return key; // Return the sum of ASCII values as the key
}
string decimalToTernary(int num)
{
    string result;
    if (num == 0)
        return "0";
    while (num > 0)
    {
        result = to_string(num % 3) + result;
        num /= 3;
    }
    return result;
}

// // Static variables for tracking probe counts
// static int probeCount = 0;                     // Tracks the probe count for the current operation
// static map<string, pair<int, int>> probeStats; // Maps operation types to <totalProbes, operationCount>

// // Start probe counting
// void startProbeCounting()
// {
//     probeCount = 0; // Reset probe count at the start of the operation
// }

// // Record probe count for a specific operation
// void recordProbeCount(const string &operation, bool success)
// {
//     string key;

//     // Distinguish between successful and unsuccessful search operations
//     if (operation == "search")
//     {
//         key = success ? "successful_search" : "unsuccessful_search";
//     }
//     else if (operation == "insert")
//     {
//         key = "insert";
//     }
//     else if (operation == "delete")
//     {
//         key = "delete";
//     }
//     else
//     {
//         return; // Ignore invalid operations
//     }

//     // Update the total probe count and operation count for the specified operation
//     probeStats[key].first += probeCount;
//     probeStats[key].second += 1;
// }

// // Get average probe count for a specific operation type
// float getAverageProbeCount(const string &operationType)
// {
//     auto &[totalProbes, operationCount] = probeStats[operationType];
//     return (operationCount == 0) ? 0 : static_cast<float>(totalProbes) / operationCount;
// }

// // Reset all probe counts
// void resetProbeCounts()
// {
//     probeStats.clear();
// }

// // Get the current probe count
// int getProbeCount()
// {
//     return probeCount;
// }
// void incrementProbeCount()
// {
//     probeCount++;
// }

// // Get probe stats (const reference to the map)
// const map<string, pair<int, int>> &getProbeStats()
// {
//     return probeStats;
// }

// void printProbeStats() {
//     const auto& stats = getProbeStats(); // Retrieve probe stats

//     // List of all operation types we want to track
//     std::vector<std::string> operationTypes = {"successful_search", "unsuccessful_search", "insert", "delete"};

//     cout << "Probe Statistics:" << endl;

//     // Loop through all operations and print stats
//     for (const auto& operationType : operationTypes) {
//         // Check if the operation type exists in the stats map
//         auto it = stats.find(operationType);
//         int totalProbes = 0;
//         int operationCount = 0;
//         float averageProbes = 0.0;

//         // If the operation type exists, retrieve its values
//         if (it != stats.end()) {
//             totalProbes = it->second.first;
//             operationCount = it->second.second;
//             averageProbes = (operationCount == 0) ? 0 : static_cast<float>(totalProbes) / operationCount;
//         }

//         // Print the statistics for the operation
//         cout << "Operation: " << operationType << endl;
//         cout << "  Total Probes: " << totalProbes << endl;
//         cout << "  Operation Count: " << operationCount << endl;
//         cout << "  Average Probes: " << averageProbes << endl;
//         cout << endl;
//     }
// }

// // void printProbeStats()
// // {
// //     const auto &stats = getProbeStats(); // Retrieve probe stats

// //     cout << "Probe Statistics:" << endl;
// //     for (const auto &[operationType, stats] : stats)
// //     {
// //         auto [totalProbes, operationCount] = stats;
// //         float averageProbes = (operationCount == 0) ? 0 : static_cast<float>(totalProbes) / operationCount;

// //         cout << "Operation: " << operationType << endl;
// //         cout << "  Total Probes: " << totalProbes << endl;
// //         cout << "  Operation Count: " << operationCount << endl;
// //         cout << "  Average Probes: " << averageProbes << endl;
// //         cout << endl;
// //     }
// // }

void testDatastructures()
{
    char choice;

    do
    {
        // Prompt user to choose the type of data structure
        cout << "Choose the type of data structure:" << endl;
        cout << "1. Open hashing with unsorted lists" << endl;
        cout << "2. Open hashing with sorted lists" << endl;
        cout << "3. Closed hashing with linear probing" << endl;
        cout << "4. Binary search tree" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            handleUnsortedHashTable();
            break;

        case '2':
            handleSortedHashTable();
            break;

        case '3':
            handleLinearProbingHashTable();
            break;

        case '4':
            handleBinarySearchTree();
            break;

        case '5':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

    } while (choice != '5');
    // LinearProbingHashTable hashTable(size);
}

void handleUnsortedHashTable()
{
    int size;
    cout << "Enter the size of the hash table: ";
    std::cin >> size;
    unsortedListHashTable unsortedTable(size);

    char choice;
    string key;

    do
    {
        cout << "\nChoose an operation: " << endl;
        cout << "1. Insert key" << endl;
        cout << "2. Delete key" << endl;
        cout << "3. Search key" << endl;
        cout << "4. Display hash table" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "Enter key to insert: ";
            std::cin >> key;
            unsortedTable.insert(key);
            break;

        case '2':
            cout << "Enter key to delete: ";
            std::cin >> key;
            unsortedTable.remove(key);
            break;

        case '3':
            cout << "Enter key to search: ";
            std::cin >> key;
            unsortedTable.search(key);
            break;

        case '4':
            unsortedTable.display();
            break;

        case '5':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

    } while (choice != '5');
}

void handleSortedHashTable()
{
    int size;
    cout << "Enter the size of the hash table: ";
    std::cin >> size;
    sortedListHashTable sortedTable(size);

    char choice;
    string key;

    do
    {
        cout << "\nChoose an operation: " << endl;
        cout << "1. Insert key" << endl;
        cout << "2. Delete key" << endl;
        cout << "3. Search key" << endl;
        cout << "4. Display hash table" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "Enter key to insert: ";
            std::cin >> key;
            sortedTable.insert(key);
            break;

        case '2':
            cout << "Enter key to delete: ";
            std::cin >> key;
            sortedTable.remove(key);
            break;

        case '3':
            cout << "Enter key to search: ";
            std::cin >> key;
            sortedTable.search(key);
            break;

        case '4':
            sortedTable.display();
            break;

        case '5':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

    } while (choice != '5');
}

void handleLinearProbingHashTable()
{
    int size;
    cout << "Enter the size of the hash table: ";
    std::cin >> size;
    LinearProbingHashTable linearProbingTable(size);

    char choice;
    string key;

    do
    {
        cout << "\nChoose an operation: " << endl;
        cout << "1. Insert key" << endl;
        cout << "2. Delete key" << endl;
        cout << "3. Search key" << endl;
        cout << "4. Display hash table" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "Enter key to insert: ";
            std::cin >> key;
            linearProbingTable.insert(key);
            break;

        case '2':
            cout << "Enter key to delete: ";
            std::cin >> key;
            linearProbingTable.remove(key);
            break;

        case '3':
            cout << "Enter key to search: ";
            std::cin >> key;
            linearProbingTable.search(key);
            break;

        case '4':
            linearProbingTable.display();
            break;

        case '5':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

    } while (choice != '5');
}

void handleBinarySearchTree()
{
    BinarySearchTree bst;

    char choice;
    string key;

    do
    {
        cout << "\nChoose an operation: " << endl;
        cout << "1. Insert key" << endl;
        cout << "2. Delete key" << endl;
        cout << "3. Search key" << endl;
        cout << "4. Display tree" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "Enter key to insert: ";
            std::cin >> key;
            bst.insert(key);
            break;

        case '2':
            cout << "Enter key to delete: ";
            std::cin >> key;
            bst.remove(key);
            break;

        case '3':
            cout << "Enter key to search: ";
            std::cin >> key;
            bst.search(key);
            break;

        case '4':
            bst.display();
            break;

        case '5':
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please choose again." << endl;
        }

    } while (choice != '5');
}

void inputHandling()
{

    int m;           // Hash table size
    int n;           // Number of initial insertions
    vector<int> M;   // Methods to investigate
    int I;           // Decimal number for ternary string
    string filename; // Name of the text file

    // Input handling
    cout << "Enter hash table size (m): ";
    cin >> m;

    cout << "Enter initial number of insertions (n): ";
    cin >> n;
    string methodInput;
    cout << "Enter the set of methods(M) to investigate (e.g., 1 2 3 4 (1-4)): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, methodInput); // Read the entire line of input
    istringstream iss(methodInput);
    int method;
    while (iss >> method)
    {
        M.push_back(method);
    }

    cout << "Enter a decimal number (I): ";
    cin >> I;

    cout << "Enter the name of the text file: ";
    cin >> filename;

    // Convert decimal number to ternary string
    string ternaryString = decimalToTernary(I);
    // Output the inputs for verification
    cout << "Hash table size (m): " << m << endl;
    cout << "Number of initial insertions (n): " << n << endl;
    cout << "Methods to investigate: ";
    for (int method : M)
    {
        cout << method << " ";
    }
    cout << endl;
    cout << "Ternary string: " << ternaryString << endl;

    // Here you would initialize your data structures and run the experiments
    // using the provided inputs.

    ifstream inFile;
    string directory_name = "D:\\DSA Assignment\\";
    string file_location = directory_name + filename;
    inFile.open(file_location);
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1);
    }

    char forbiddenSet[] = {',', '.', ' '}; // Forbidden characters
    vector<string> tokens;                 // Vector to store tokens
    string currentToken;                   // To accumulate characters for each token

    char ch; // For reading character by character
    while (inFile.get(ch))
    { // Read the file character by character
        bool isForbidden = false;

        // Check if the character is forbidden
        for (char forbidden : forbiddenSet)
        {
            if (ch == forbidden)
            {
                isForbidden = true;
                break;
            }
        }

        // If the character is forbidden, process the current token
        if (isForbidden)
        {
            if (!currentToken.empty())
            {
                // Adjust token to exactly 10 characters
                string adjustedToken = adjustTokenLength(currentToken);
                tokens.push_back(adjustedToken); // Store the adjusted token
                currentToken.clear();            // Reset for next token
            }
        }
        else
        {
            // If not forbidden, add the character to the current token
            currentToken += ch;
        }
    }

    // Handle any remaining token after the end of the file
    if (!currentToken.empty())
    {
        string adjustedToken = adjustTokenLength(currentToken);
        tokens.push_back(adjustedToken);
    }

    inFile.close(); // Close the file

    // Display the processed tokens
    cout << "Processed Tokens (Length = 10):" << endl;
    for (const string &t : tokens)
    {
        cout << t << "Key" << generateKey(t) << endl;
    }
}
