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

// direction 0 1 2 3 4 5 6 7 8 correspond to each direction

int dfs(int i, int j, vector<string>& grid, char neededLetter, int direction) {
    
    unordered_set<char> letters = {'X','M','A','S'};
    vector<vector<int>> dir = {{-1,-1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1,0},{1,1}};

    int n = grid.size(), m = grid[0].size();
    if (i < 0 || i >= n || j < 0 || j >= m) return 0;

    char currentLetter = grid[i][j];
    if (currentLetter != neededLetter) return 0;

    if (currentLetter == 'S') return 1;

    int occurances = 0;

    char nextLetter = '\0';
    if (currentLetter == 'X') nextLetter = 'M';
    else if (currentLetter == 'M') nextLetter = 'A';
    else if (currentLetter == 'A') nextLetter = 'S';

    occurances += dfs(i+dir[direction][0], j+dir[direction][1], grid, nextLetter, direction);

    return occurances;

}

int howManyTimes(vector<string>& grid) {

    int n = grid.size(), m = grid[0].size(), sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                for (int d = 0; d < 9; d++) {
                    sum += dfs(i, j, grid, 'X', d);
                }
            }
        }
    }

    return sum; 



}

bool inBounds(vector<vector<int>>& vec, int n, int m) {

    for (vector<int>& v : vec) {
        int i = v[0], j = v[1];
        if (i < 0 || i >= n || j < 0 || j >= m) return false;
    }

    return true;

}

bool validXmas(int i, int j, vector<string>& grid) {

    int n = grid.size(), m = grid[0].size();
    
    vector<int> topLeft, topRight, bottomLeft, bottomRight;

    topLeft = {i-1, j-1};
    topRight = {i-1, j+1};
    bottomLeft = {i+1, j-1};
    bottomRight = {i+1, j+1};

    vector<vector<int>> indexes = {topLeft, topRight, bottomLeft, bottomRight};

    if (!inBounds(indexes, n, m)) return false;

    // cout << "index: (" << i << "," << j << ") ";
    string diag1 = "", diag2 = "";

    diag1 += grid[topLeft[0]][topLeft[1]];
    diag1 += grid[i][j];
    diag1 += grid[bottomRight[0]][bottomRight[1]];

    diag2 += grid[bottomLeft[0]][bottomLeft[1]];
    diag2 += grid[i][j]; 
    diag2 += grid[topRight[0]][topRight[1]];

    // cout << diag1 << " " << diag2 << '\n';

    if (diag1 != "MAS" && diag1 != "SAM") return false;
    if (diag2 != "MAS" && diag2 != "SAM") return false;

    return true;


}


int howManyXMas(vector<string>& grid) {

    int n = grid.size(), m = grid[0].size(), sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A'){
                // sum += validXmas(i, j, grid);
                if (validXmas(i,j,grid)) sum++;
            }
        }
    }

    return sum;




}


int main() {

    // take in input
    ifstream input("test.txt");

    vector<string> grid;

    // initialise grid
    string line;
    while(getline(input, line)) {
        grid.push_back(line);
    }

    cout << howManyTimes(grid) << '\n';
    cout << howManyXMas(grid) << '\n';

    return 0;

}

