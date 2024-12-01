#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <unordered_map>


// partA
long long solveA(std::priority_queue<int, std::vector<int> >& a, std::priority_queue<int, std::vector<int> >& b) {

    // initialise the sum of the differences
    long long sum_of_differences = 0;

    // while there are elements left in both lists
    while (!a.empty() && !b.empty()) {

        // obtain sum of difference
        sum_of_differences += std::abs(a.top() - b.top());
        a.pop(); b.pop();
    
    }

    return sum_of_differences;

}

// partB
long long solveB(std::vector<int>& a, std::unordered_map<int,int>& map) {

    // initialise similarity score
    long long similarity_score = 0;

    for (int value : a) {
        similarity_score += (value * map[value]);
    }

    return similarity_score;

}


int main() {

    // take in input
    std::ifstream input("text.txt");

    // check whether the file has been opened
    if (!input.is_open()) return 1;

    // PART A: create two priority queues
    std::priority_queue<int, std::vector<int>> a, b;

    // PART B: create a map
    std::vector<int> leftList;
    std::unordered_map<int,int> frequency;

    // obtain each line of the input text
    std::string line;
    while (std::getline(input, line)) {

        // separate the input into values from the left list and right list
        int separatingIdx = line.find(" ");
        int left = stoi(line.substr(0, separatingIdx));
        int right = stoi(line.substr(separatingIdx+1));

        // part A
        a.push(left);
        b.push(right);

        // part B
        leftList.push_back(left);
        frequency[right]++;


    }

    input.close();

    // output the result
    std::cout << solveA(a, b) << '\n';
    std::cout << solveB(leftList, frequency) << '\n';

    return 0;

}




