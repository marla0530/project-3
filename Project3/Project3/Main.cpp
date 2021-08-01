#include "vecVector.h"
#include "bst.h"
#include <istream>
#include <sstream>
#include <fstream>
#include <chrono>
#include "maxHeap.h"
#include "minHeap.h"
#include <map>

using namespace std::chrono;

typedef high_resolution_clock Clock;

void clearCin() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

int main()
{
    vecVector vV;
    BST tree;
    maxHeap heapMax;
    minHeap heapMin;

    bool program = true;
    bool fileAccessed = false;
    int dataStrucsUsed = 0;
    int menu = 0;
    map<string, int> dataStrucs;


    vector<pair<string, double>> top25Vector;
    vector<pair<string, double>> top25Tree;
    vector<pair<string, double>> top25Max;
    vector<pair<string, double>> top25Min;


    cout << "Welcome to the Football Top 25 Power Ranking program!" << endl;

    while (!fileAccessed) {
        string fileName = "";

        cout << "Please enter CSV file name: " << endl;
        try {
            cin >> fileName;
        }
        catch (exception& e) {
            cout << "ERROR: Bad Input, Please Try Again";
        }

        ifstream inFile(fileName + ".csv");
        if (inFile.is_open())
        {
            cout << "reading data......" << endl;
            string headers;
            string team;
            string line;
            string temp;
            double power;
            getline(inFile, headers);
            for (int i = 0; i < 50000; i++) {
                getline(inFile, line);
                istringstream stream(line);
                getline(stream, team, ',');
                getline(stream, temp);
                power = stod(temp);
                vV.insert(power, team);
                tree.root = tree.insert(tree.root, power, team);
                heapMax.insert(team, power);
                heapMin.insert(team, power);
            }
            fileAccessed = true;
        }
        else {
            cout << "Please Try Again" << endl;
            clearCin();
        }
        inFile.close();

    }
    clearCin();

    cout << "Complete" << endl;
    cout << endl;

    while (program) {
        cout << "Data Structures Used So Far : " << dataStrucsUsed << endl;
        cout << "Main Menu: " << endl;
        cout << "1. Find Using Array Vector" << endl;
        cout << "2. Find Using Kth Largest Binary Search Tree" << endl;
        cout << "3. Find Using Max Heap" << endl;
        cout << "4. Find Using Min Heap" << endl;
        cout << "5. Compare Used Data Structures" << endl;
        cout << "6. Exit Program" << endl;
        cout << endl;

        try {
            cin >> menu;
        }
        catch (exception& e) {
            cout << "ERROR: Bad Input, Please Try Again";
        }

        switch (menu) {
        case 1: {
            cout << "Array Vector approach" << endl;
            cout << endl;
            auto t1 = Clock::now();
            top25Vector = vV.topX(25);
            auto t2 = Clock::now();


            for (int i = 0; i < top25Vector.size(); i++) {
                cout << i + 1 << ". " << top25Vector[i].first << " with a rank of " << top25Vector[i].second << endl;
            }


            cout << "search time: " << duration_cast<nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;
            cout << endl;

            dataStrucs["Array"] = duration_cast<nanoseconds>(t2 - t1).count();
            break;
        }
        case 2: {
            cout << "K th largest from a BST approach" << endl;
            cout << endl;
            auto t1 = Clock::now();
            tree.topX(25);
            top25Tree = tree.getResult();
            auto t2 = Clock::now();

            for (int i = 0; i < top25Tree.size(); i++) {
                cout << i + 1 << ". " << top25Tree[i].first << " with a rank of " << top25Tree[i].second << endl;
            }
            cout << "search time: " << duration_cast<nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;
            cout << endl;

            dataStrucs["Kth Largest BST"] = duration_cast<nanoseconds>(t2 - t1).count();
            break;
        }
        case 3: {

            if (dataStrucs.find("Max Heap") != dataStrucs.end()) {
                cout << "Max Heap Already Used!" << endl;
                cout << "Grabbing earlier data..." << endl;

            }
            else {
                auto t1 = Clock::now();
                top25Max = heapMax.topX(25);
                auto t2 = Clock::now();
                dataStrucs["Max Heap"] = duration_cast<nanoseconds>(t2 - t1).count();
            }

            cout << "Max Heap Approach: " << endl;



            for (int i = 0; i < top25Max.size(); i++) {
                cout << i + 1 << ". " << top25Max[i].first << " with a rank of " << top25Max[i].second << endl;
            }



            cout << "search time: " << dataStrucs["Max Heap"] << " nanoseconds" << endl;
            cout << endl;


            break;
        }
        case 4: {
            if (dataStrucs.find("Min Heap") != dataStrucs.end()) {
                cout << "Min Heap Already Used!" << endl;
                cout << "Grabbing earlier data..." << endl;
            }
            else {
                auto t1 = Clock::now();
                top25Min = heapMin.topX(25);
                auto t2 = Clock::now();
                dataStrucs["Min Heap"] = duration_cast<nanoseconds>(t2 - t1).count();
            }





            for (int i = 0; i < top25Min.size(); i++) {
                cout << i + 1 << ". " << top25Min[i].first << " with a rank of " << top25Min[i].second << endl;
            }



            cout << "search time: " << dataStrucs["Min Heap"] << " nanoseconds" << endl;
            cout << endl;



            break;

        }
        case 5: {

            int fastest = INT_MAX;
            auto structure = dataStrucs.begin();

            if (dataStrucsUsed <= 1) {
                cout << "Need more data structures used to perform a comparison" << endl;
            }
            else {
                for (auto iter = dataStrucs.begin(); iter != dataStrucs.end(); iter++) {
                    cout << "Structure: " << iter->first << " finished in " << iter->second << " nanoseconds." << endl;

                    if (iter->second < fastest) {
                        fastest = iter->second;
                        structure = iter;
                    }
                }
                cout << endl << endl;
                cout << "The fastest data structure so far is " << structure->first << " at " << structure->second << " nanoseconds" << endl;
            }
            break;
        }
        case 6: {
            program = false;
            cout << "Goodbye!" << endl;
            break;
        }
        default: {
            cout << "Sorry, there is no menu item assigned to that number! Please try again" << endl;
            break;
        }


        }
        dataStrucsUsed = dataStrucs.size();
    }













    return 0;
}