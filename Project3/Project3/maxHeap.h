#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

class maxHeap {
private:
    vector<pair<string, double>> heap;

public:

    void insert(string name, double power);
    void pop();
    pair<string, double> checkTop();

    bool insertCSV(string filename);

    vector<pair<string, double >> topX(int x);



};
