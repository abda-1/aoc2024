#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <stack>
#include <algorithm>

using namespace std;

// correctly order and incorrect ordering
int correctlyOrder(vector<int>& ordering, unordered_map<int, unordered_set<int>>& valuesAfter) {

    sort(ordering.begin(), ordering.end(), [&valuesAfter](int a, int b){
        return valuesAfter[a].find(b) != valuesAfter[a].end();
    });

    return ordering[ordering.size()/2];

}


int validOrdering(vector<int>& ordering, unordered_map<int, unordered_set<int>>& valuesAfter, bool partA) {

    // for each element, check that 
    for (int i = 0; i < ordering.size(); i++) {
        for (int j = i+1; j < ordering.size(); j++) {
            if (valuesAfter[ordering[i]].find(ordering[j]) == valuesAfter[ordering[i]].end()) {
                if (partA) return 0;                
                return correctlyOrder(ordering, valuesAfter);
            }
        }
    }

    if (!partA) return 0;

    // find middle value and return;
    int n = ordering.size();
    return ordering[n/2];

}

int solve(vector<vector<int>>& orderings, unordered_map<int, unordered_set<int>>& valuesAfter, bool partA) {

    int sum = 0;
    for (vector<int> ordering : orderings) {
        sum += validOrdering(ordering, valuesAfter, partA);
    }

    return sum; 

}

int main() {

    // take in input
    ifstream rules("test.txt");
    ifstream updates("testUpdates.txt");

    unordered_map<int, unordered_set<int>> valuesAfter;

    // initialise grid
    string line;
    while(getline(rules, line)) {
        
        int delim = line.find('|');
        int valueA = stoi(line.substr(0, delim));
        int valueB = stoi(line.substr(delim+1, line.length()-delim));
        
        valuesAfter[valueA].insert(valueB);
    }


    // reading in updates
    vector<vector<int>> orderings;
    while(getline(updates, line)) {
        
        stringstream ss(line);
        string value;
        vector<int> ordering;

        while(getline(ss, value, ',')){
            ordering.push_back(stoi(value));
        }
        orderings.push_back(ordering);
        
    }

    cout << solve(orderings, valuesAfter, true) << '\n';
    cout << solve(orderings, valuesAfter, false) << '\n';

    return 0;

}

