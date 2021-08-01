#include "maxHeap.h"


void maxHeap::insert(string name, double power) {
    //Push new element to the end
    heap.push_back(make_pair(name, power));

    //Check to see if the vector is empty
    if (!heap.empty()) {
        int pos = heap.size() - 1;
        int parent = (pos - 1) / 2;

        //Loop to the root to see if inserted element is larger
        while ((parent >= 0) && ((heap[pos].second > heap[parent].second) || ((heap[pos].second == heap[parent].second) && heap[pos].first < heap[parent].first))) {
            auto temp = heap[parent];
            heap[parent] = heap[pos];
            heap[pos] = temp;
            pos = parent;
            parent = (pos - 1) / 2;
        }
    }
    return;
}

void maxHeap::pop() {

    //Swap the first and last elements
    auto temp = heap[heap.size() - 1];
    heap[heap.size() - 1] = heap[0];
    heap[0] = temp;
    //Delete last/largest element
    heap.pop_back();

    int pos = 0;
    bool smaller = true;

    //Check to see if it has at least one child.
    while (heap.size() > (pos * 2) + 1 && smaller) {
        double left = heap[(pos * 2) + 1].second;
        double right = (heap.size() > ((pos * 2) + 2)) ? heap[(pos * 2) + 2].second : 0;

        int largestChild;
        //Compare child powers
        if (left > right) {
            largestChild = (pos * 2) + 1;
        }
        else if (left == right && heap[(pos * 2) + 1].first < heap[(pos * 2) + 2].first) {
            largestChild = (pos * 2) + 1;
        }
        else {
            largestChild = (pos * 2) + 2;
        }

        if (heap[pos].second < heap[largestChild].second) {
            temp = heap[largestChild];
            heap[largestChild] = heap[pos];
            heap[pos] = temp;
            pos = largestChild;
        }
        else {
            smaller = false;
        }
    }
    return;


}

pair<string, double> maxHeap::checkTop() {
    return heap[0];
}

bool maxHeap::insertCSV(string filename) {
    ifstream CSVFile(filename + ".csv");
    string line;
    getline(CSVFile, line);

    while (getline(CSVFile, line)) {
        istringstream inSS(line);
        string name;
        string power;

        getline(inSS, name, ',');
        getline(inSS, power, ',');
        insert(name, stod(power));
    }
    return true;
}

vector<pair<string, double >> maxHeap::topX(int x) {
    vector<pair<string, double>> temp;

    for (unsigned int i = 0; i < x; i++) {
        temp.push_back(checkTop());
        pop();
    }

    return temp;
}