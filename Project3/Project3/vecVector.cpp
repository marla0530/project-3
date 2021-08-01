#include "vecVector.h"
//create vector of vector
vecVector::vecVector() {
	for (int i = 0; i < 10001; i++) {
		vector <string> temp;
		table.push_back(temp);
	}
}

//multiply the key by 100 so it can be used as index in the vector
int vecVector::hashFunction(double& key) {
	return key * 100;
}

void vecVector::insert(double& key, string& teamName) {
	int index = hashFunction(key);

	//keep track of team with highest power level in the vector
	if (index > largest) {
		largest = index;
	}

	//add the new team in
	table[index].push_back(teamName);
}
vector<pair<string, double >> vecVector::topX(int x) {
	vector<pair<string, double >> outPut;
	int count = 0;
	int temp = largest;

	//return the top x teams
	while (count < x) {

		//print out all of the teams in vector with highest power level
		for (int i = 0; i < table[temp].size(); i++) {

			//push it to the vector
			outPut.push_back(make_pair(table[temp][i], temp / 100.0));

			//increment count
			count++;

			//stop after we reach the number of team we want
			if (count == x) {
				break;
			}
		}

		//look for the next highest vector by incrementing 1 value down until an vector that is not empty
		for (int i = temp - 1; temp > -1; i--)
		{
			if (table[i].size() != 0) {
				temp = i;
				break;
			}
		}
	}

	return outPut;
}
