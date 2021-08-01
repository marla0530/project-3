#pragma once
using namespace std;
#include <vector>
#include<string>
#include <iostream>
#include <stack>


class minHeap {
    vector<pair<string, double>> heap;
public:
        void insert(string teams, double powerLevel);
        void pop();
        vector<pair<string, double >> topX(int x);
        void filterUp(int index);
        void heapifyDown(int index);
        stack<pair<string, double>> storeData();

};