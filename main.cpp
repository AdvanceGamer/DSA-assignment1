#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <limits>
#include <cmath>
#include "closed_hashing_linear_probing.h"
#include "open_hashing_sorted_list.h"
#include "open_hashing_unsorted_list.h"
#include "binary_search_tree.h"
#include "utility_functions.h"

using namespace std;

int main()
{
    // testDatastructures();
    // inputHandling();

    int m;           // Hash table size
    int n;           // Number of initial insertions
    vector<int> M;   // Methods to investigate
    int I;           // Decimal number for ternary string
    string filename; // Name of the text file

    // Input handling
    std::cout << "Enter hash table size (m): ";
    cin >> m;

    std::cout << "Enter initial number of insertions (n): ";
    cin >> n;
    string methodInput;
    std::cout << "Enter the set of methods(M) to investigate (e.g., 1 2 3 4 (1-4)): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, methodInput); // Read the entire line of input
    istringstream iss(methodInput);
    int method;
    while (iss >> method)
    {
        M.push_back(method);
    }

    std::cout << "Enter a decimal number (I): ";
    cin >> I;

    std::cout << "Enter the name of the text file: ";
    cin >> filename;

    // Convert decimal number to ternary string
    string ternaryString = decimalToTernary(I);
    // Output the inputs for verification
    std::cout << "Hash table size (m): " << m << endl;
    std::cout << "Number of initial insertions (n): " << n << endl;
    std::cout << "Methods to investigate: ";
    for (int method : M)
    {
        std::cout << method << " ";
    }
    std::cout << endl;
    std::cout << "Ternary string: " << ternaryString << endl;

    // Here you would initialize your data structures and run the experiments
    // using the provided inputs.

    ifstream inFile;
    string directory_name = "D:\\New folder (13)\\";
    string file_location = directory_name + filename;
    inFile.open(file_location);
    if (!inFile)
    {
        std::cout << "Unable to open file";
        exit(1);
    }

    char forbiddenSet[] = {',', '.', ' '}; // Forbidden characters
    vector<string> tokens;                 // Vector to store tokens
    string currentToken;                   // To accumulate characters for each token

    char ch; // For reading character by character
    // int temp=1;
    // int temp2=50;
    // while(inFile.get(ch)){
    //     if(temp<=temp2){
    //         std::cout<<ch;
    //     }
    //     else{
    //         std::cout<<ch<<endl;
    //         temp=1;
    //     }
    //      temp+=1;
    // }
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
    // std::cout << "Processed Tokens (Length = 10):" << endl;
    // // int temp=1;
    // for (const string &t : tokens)
    // {
    //     std::cout << "Token: " << t << " Key : " << generateKey(t) << endl;
    // }

    vector<string> setDatastructureTokens;
    vector<string> performDatastructureTokens;
    int i = 0;
    // std::cout << "HI";
    while (i < n && i < tokens.size())
    {
        setDatastructureTokens.push_back(tokens[i]);
        i++;
    }
    // std::cout << "HI2";
    while (i < tokens.size())
    {
        performDatastructureTokens.push_back(tokens[i]);
        i++;
    }
    // std::cout << "HI3";
    // tokens.clear();
    // delete &tokens;
    // std::cout << "HI4";
    // setting datastructure

    for (int method : M)
    {
        // std::cout<<"M : "<<method<<" i: "<<i<<endl;
        if (method == 1)
        {
            // setting data structure
            std::cout << " Setting up.. open hashing unsorted list" << endl;
            unsortedListHashTable hashtable1(m);
            int i = 0;
            while (i < n)
            {
                hashtable1.insert(setDatastructureTokens[i]);
                i++;
            }
            // performing operations
            std::cout << "open hashing unsorted list->" << endl;
            // hashtable1.display();
            hashtable1.metric.resetProbeCounts();
            i = 0;
            std::cout << "performing operations..." << endl;
            if (hashtable1.metric.getProbeStats().empty())
            {

                for (char ch : ternaryString)
                {
                    // printProbeStats();
                    if (ch == '0')
                    {
                        hashtable1.search(performDatastructureTokens[i]);
                    }
                    else if (ch == '1')
                    {
                        hashtable1.insert(performDatastructureTokens[i]);
                    }
                    else
                    {
                        hashtable1.remove(performDatastructureTokens[i]);
                    }
                    i++;
                }
                std::cout << "Probe Stats of open hashing unsorted list";
                hashtable1.metric.printProbeStats();
            }
        }
        else if (method == 2)
        {
            // setting data structure
            std::cout << " Setting up.. open hashing sorted list" << endl;
            sortedListHashTable hashtable2(m);
            int i = 0;
            while (i < n)
            {
                hashtable2.insert(setDatastructureTokens[i]);
                i++;
            }
            std::cout << "open hashing sorted list->" << endl;
            // hashtable2.display();
            // performing operations
            // printProbeStats();
            hashtable2.metric.resetProbeCounts();
            // printProbeStats();
            i = 0;
            std::cout << "performing operations..." << endl;
            if (hashtable2.metric.getProbeStats().empty())
            {
                for (char ch : ternaryString)
                {
                    // printProbeStats();
                    // hashtable2.display();
                    if (ch == '0')
                    {
                        hashtable2.search(performDatastructureTokens[i]);
                    }
                    else if (ch == '1')
                    {
                        hashtable2.insert(performDatastructureTokens[i]);
                    }
                    else
                    {
                        hashtable2.remove(performDatastructureTokens[i]);
                    }
                    i++;
                }
                std::cout << "Probe Stats of open hashing sorted list";
                hashtable2.metric.printProbeStats();
            }
        }
        else if (method == 3)
        {
            // setting data structure
            std::cout << " Setting up.. closed hashing linear probing" << endl;
            LinearProbingHashTable hashtable3(m);
            int i = 0;
            while (i < n)
            {
                // hashtable3.metric.printProbeStats();
                hashtable3.insert(setDatastructureTokens[i]);
                i++;
            }
            std::cout << "closed hashing linear probing->" << endl;
            // hashtable3.display();
            // performing operations

            i = 0;
            std::cout << "performing operations..." << endl;
            hashtable3.metric.resetProbeCounts();
            if (hashtable3.metric.getProbeStats().empty())
            {
                for (char ch : ternaryString)
                {
                    // printProbeStats();
                    if (ch == '0')
                    {
                        hashtable3.search(performDatastructureTokens[i]);
                    }
                    else if (ch == '1')
                    {
                        hashtable3.insert(performDatastructureTokens[i]);
                    }
                    else
                    {
                        hashtable3.remove(performDatastructureTokens[i]);
                    }
                    i++;
                }
                std::cout << "Probe Stats of closed hashing linear probing";
                hashtable3.metric.printProbeStats();
            }
        }
        else if (method == 4)
        {
            std::cout << " Setting up... binary search tree" << endl;
            // setting data structure
            BinarySearchTree bst;
            int i = 0;
            while (i < n)
            {
                bst.insert(setDatastructureTokens[i]);
                i++;
            }
            // performing operations
            std::cout << " performing operations... " << endl;
            bst.metric.resetProbeCounts();
            i = 0;
            if (bst.metric.getProbeStats().empty())
            {
                for (char ch : ternaryString)
                {
                    // printProbeStats();
                    if (ch == '0')
                    {
                        bst.search(performDatastructureTokens[i]);
                    }
                    else if (ch == '1')
                    {
                        bst.insert(performDatastructureTokens[i]);
                    }
                    else
                    {
                        bst.remove(performDatastructureTokens[i]);
                    }
                    i++;
                }
                std::cout << "Probe Stats of Binary Search Tree";
                bst.metric.printProbeStats();
            }
        }
    }
    // testDatastructures();
    return 0;
}