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

/*
directions:
0 - up
1 - right
2 - down
3 - left
*/ 

vector<vector<int>> directions = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};

char nextCellValue(int i, int j, vector<string>& grid, int direction) {

    //                                  up     right   down     left
    vector<vector<int>> directions = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};

    int x = i+directions[direction][0], y = j+directions[direction][1];

    int n = grid.size(), m = grid[0].size();
    if (x < 0 || x >= n || y < 0 || y >= m) return ' ';

    return grid[x][y];

}

void fillGrid(int i, int j, vector<string>& grid, int direction) {

    int n = grid.size(), m = grid[0].size();

    if (i < 0 || i >= n || j < 0 || j >= m) return;

    // mark the current cell as visited
    grid[i][j] = 'X';

    // explore other directions if need be
    if (nextCellValue(i, j, grid, direction) == '#') {
        // rotate direction
        return fillGrid(i, j, grid, (direction+1)%4);
    }

    vector<vector<int>> directions = {{-1,0}, {0, 1}, {1, 0}, {0, -1}};
    int x = i+directions[direction][0], y = j+directions[direction][1];
    return fillGrid(x, y, grid, direction);




}


int solve(vector<string>& grid, bool partA) {

    // find the ^
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^') fillGrid(i, j, grid, 0);
        }
    }

    // count X
    int sum = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X') sum++;
        }
    }

    return sum;

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
    

    cout << solve(grid, true) << '\n';

    return 0;

}

