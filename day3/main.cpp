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
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
*/

bool isNumber(string& s)  {

    // need to be 3 digits or less
    if (s.length() > 3) return false;

    // need to all digits
    unordered_set<char> digits = {'1','2','3','4','5','6','7','8','9','0'};

    for (char c : s) {
        if (digits.find(c) == digits.end()) return false;
    }

    return true;
}

int isValid(string& command, int open, int close) {

    // error case
    int comma = open;
    if (close-open > 8 || (comma = command.find_first_of(',', open)) == string::npos) return 0; 

    // create the substrings for X and for Y
    string x = command.substr(open+1, comma-open-1);
    string y = command.substr(comma+1, close-comma-1);

    // ensure that XXX and YYY are valid
    if (!isNumber(x) || !isNumber(y)) return 0;

    cout << "valid: " << x << "," << y << '\n';

    return (long long)(stoi(x) * stoi(y));

}

int isValid2(string& command, int open, int close, vector<int>& enable, vector<int>& disable) {

    // error case
    int comma = open;
    if (close-open > 8 || (comma = command.find_first_of(',', open)) == string::npos) return 0; 

    // create the substrings for X and for Y
    string x = command.substr(open+1, comma-open-1);
    string y = command.substr(comma+1, close-comma-1);

    // ensure that XXX and YYY are valid
    if (!isNumber(x) || !isNumber(y)) return 0;

    // check to see whether the most recent function call was enable or disable
    int recent_enable = 0, recent_disable = -2;

    // optimise here to include binary search
    for (int i = 0; i < enable.size(); i++) {
        if (enable[i] >= open) break;
        recent_enable = enable[i];
    }

    for (int i = 0; i < disable.size(); i++) {
        if (disable[i] >= open) break;
        recent_disable = disable[i];
    }

    if (recent_enable <= recent_disable) {
        return 0;
    }

    cout << "valid: " << x << "," << y << '\n';
    
    return (long long)(stoi(x) * stoi(y));

}


long long solveA(string& command) {

    // find all instances of "mul(" within the string

    int start = 0;
    long long sum = 0;

    while ((start = command.find("mul(", start+1)) != string::npos) {
        int open = start+3;
        int close = command.find_first_of(')', start);
        
        sum += isValid(command, open, close);

    }

    return sum;

}

long long solveB(string& command) {
    
    // create two vectors of all "do()" and "don't()" locations
    vector<int> enable, disable;

    // always start with enable
    enable.push_back(-1);

    int enable_pos = 0;
    while ((enable_pos = command.find("do()", enable_pos+1)) != string::npos) {
        enable.push_back(enable_pos);
    }

    int disable_pos = 0;
    while ((disable_pos = command.find("don't()", disable_pos+1)) != string::npos) {
        disable.push_back(disable_pos);
    }

    // for each occurance of mul that we find, we will check (using bSearch) whether enable or disable is left most
    long long sum = 0;

    int start = 0;
    while ((start = command.find("mul(", start+1)) != string::npos) {
        int open = start+3;
        int close = command.find_first_of(')', start);
        
        sum += isValid2(command, open, close, enable, disable);
        
    }

    return sum;
}

int main() {

    // take in input
    ifstream input("test.txt");

    // initialise reports
    string command = "";
    string line;
    while(getline(input, line)) {
        command += line;
    }

    cout << solveA(command) << '\n';
    cout << solveB(command) << '\n';

    return 0;

}

