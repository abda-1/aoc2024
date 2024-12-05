#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <stack>

// create a helper function to check whether a function is safe or not
bool isSafe(std::vector<int>& report) {

    if (report.size() == 1) return true;

    bool increasing = report[0] < report[1];

    for (int i = 1; i < report.size(); i++) {

        if (report[i-1] < report[i] == increasing && abs(report[i] - report[i-1]) >= 1 && abs(report[i] - report[i-1]) <= 3) {
            continue;
        }

        return false;

    }

    return true;


}

// isSafe helper for partB
bool isSafe2(std::vector<int>& report) {

    // check to see if it is already safe
    if (isSafe(report)) return true;

    bool safeWithDamp = false;

    // brute force removing every single element until we get one that is safe
    // (this is horrible, spent too long on trying to optimise)
    for (int i=0; i<report.size(); i++) {
        if (safeWithDamp) break;

        // create a copy of the report
        std::vector<int> report_copy = report;

        // remove the element
        report_copy.erase(std::next(report_copy.begin(), i));
        
        // check if safe
        safeWithDamp |= isSafe(report_copy);
    }

    return safeWithDamp;
}


// partA
long long solveA(std::vector<std::vector<int>>& reports) {

    int safe = 0;

    for (std::vector<int>& report : reports) {
        safe += isSafe(report);
    }

    return safe;
}

// partB
long long solveB(std::vector<std::vector<int>>& reports) {

    // need to have consistently increasing or decreasing
    int safe = 0;

    
    for (std::vector<int>& report : reports) {
        safe += isSafe2(report);
    }
    return safe;

}


int main() {

    // take in input
    std::ifstream input("text.txt");

    // initialise reports
    std::vector<std::vector<int>> reports;

    // obtain each line of the input text
    std::string line;
    while (std::getline(input, line)) {

        std::stringstream ss(line);
        std::string level;
        
        std::vector<int> report;
        while(ss >> level) {
            report.push_back(stoi(level));
        }

        reports.push_back(report);

    }

    std::cout << "A: " << solveA(reports) << '\n';
    std::cout << "B: " << solveB(reports) << '\n';

    return 0;

}




