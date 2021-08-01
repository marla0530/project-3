#include "minHeap.h"

void minHeap::insert(string name, double power) {
	//add new element at the end of the vector
	heap.push_back(make_pair(name, power));
	
	//filter the newly added node up the tree base off its power level
	filterUp(heap.size() - 1);

}

void minHeap::filterUp(int index) {

	int parent = (index - 1) / 2;

	//if parent is valid continue the recurssion call. The other part is here to maintain order of same powerlevel teams by their alphabetical order
	if ((parent >= 0) && ((heap[index].second < heap[parent].second) || ((heap[index].second == heap[parent].second) && heap[index].first > heap[parent].first)))
	{
		swap(heap[index], heap[parent]);
		filterUp(parent);
	}
}


void minHeap::pop() {
	//swap the root and the last element on the tree
	swap(heap[0], heap[heap.size() - 1]);

	//remove the last element on the tree
	heap.pop_back();

	//heapify the root down
	heapifyDown(0);
}


void minHeap::heapifyDown(int index) {

	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	//if left is smaller it is the smallest for now
	if (left < heap.size() && heap[smallest].second >= heap[left].second)
	{
		smallest = left;
	}

	//if right is smaller than left and index it will be the smallest
	if (right < heap.size() && heap[smallest].second >= heap[right].second) {
		smallest = right;

		//if the nodes are equal in power level sort them alphabetically
		if (heap[left].second == heap[right].second) {
			if (heap[left].first > heap[right].first) {
				smallest = left;
			}
			else {
				smallest = right;

			}
		}
	}

	//swap smallest with the index node and keep calling recurssion if index change
	if (index != smallest) {
		swap(heap[index], heap[smallest]);
		heapifyDown(smallest);
	}

}

//extract min and store it onto a stack
stack<pair<string, double>> minHeap::storeData() {
	stack<pair<string, double>> s;
	int temp = heap.size();
	for (int i = 0; i < temp; i++) {
		s.push(heap[0]);
		pop();
	}
	return s;
}

//print out the x elements in stack they should be the team with the largest power level.
vector<pair<string, double >> minHeap::topX(int x) {
	auto s = storeData();
	vector<pair<string, double >> temp;
	for (unsigned int i = 0; i < x; i++) {
		temp.push_back(s.top());
		s.pop();
	}
	return temp;
}