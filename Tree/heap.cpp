#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> data = {5, 4, 9, 8, 6, 7, 1, 3, 2, 0};

    priority_queue<int> q1;
    for (int num : data)
        q1.push(num);

    priority_queue<int, vector<int>, greater<int>> min_q1(data.begin(), data.end());

    priority_queue min_q2(data.begin(), data.end(), greater<int>());

    
}