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

bool inBounds(pair<int,int> l, int n, int m) {
    return !(l.first < 0 || l.first >= n || l.second < 0 || l.second >= m);
}

void addMany(pair<int,int> node, int x_step, int y_step, vector<string>& grid) {


    if (inBounds(node, grid.size(), grid[0].size())) {
        grid[node.first][node.second] = '#';

        pair<int,int> antinode = {node.first+x_step, node.second+y_step};
        addMany(antinode, x_step, y_step, grid);
    }
    
    return;

}

void add(pair<int,int>antinode, vector<string>& grid) {

    if (inBounds(antinode, grid.size(), grid[0].size())) {
        grid[antinode.first][antinode.second] = '#';
    }
    
    return;

}

int solve(vector<string>& grid) {

    int n = grid.size(), m = grid[0].size();

    // create a set of all types of antennas
    unordered_set<char> types;

    // create a map to store the locations of antennas - {type, vector of locations {i,j}}
    unordered_map<char, vector<pair<int,int>>> locations;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            if (grid[i][j] == '.') continue;
            if (types.find(grid[i][j]) != types.end()) {
                types.insert(grid[i][j]);
            }
            locations[grid[i][j]].push_back({i,j});
        }
    }

    // print (test)
    for (auto& [type, v] : locations) {
        cout << type << ": ";
        for (auto& l : v) cout << " (" << l.first << "," << l.second << ") ";
        cout << '\n';
    }
    
    // initialise antinode count
    int antinodeCount = 0;

    // for each location, find all pairs of antennas
    for (auto& [type, positions] : locations) {
        
        for (int i = 0; i < positions.size(); i++) {

            pair<int,int> node1 = positions[i];

            for (int j = i+1; j < positions.size(); j++) {

                pair<int,int> node2 = positions[j];

                // find the gradient between the two nodes after sorting by x value
                // attempt to move backward one step from first node and forward one step from second node
                
                // sort pair by x value
                auto left = node1.first < node2.first ? node1 : node2;
                auto right = left == node1 ? node2 : node1;

                // find the gradient between the two nodes;
                int x_step = right.first - left.first;
                int y_step = right.second - left.second;

                // attempt to add
                pair<int,int> antinode1 = {left.first - x_step, left.second - y_step};
                pair<int,int> antinode2 = {right.first + x_step, right.second + y_step};

                // add(antinode1, grid);
                // add(antinode2, grid);

                addMany(left, -x_step, -y_step, grid);
                addMany(right, x_step, y_step, grid);

            }

        }

    } 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            if (grid[i][j] == '#') antinodeCount++;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << grid[i] << '\n';
    }


    return antinodeCount;

}

int main() {

    // take in input
    ifstream rules("test.txt");

    vector<string> grid;

    // initialise grid
    string line;
    while(getline(rules, line)) {
        grid.push_back(line);
    }
    

    cout << solve(grid) << '\n';

    return 0;

}

