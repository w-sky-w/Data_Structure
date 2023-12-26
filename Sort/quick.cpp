#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int part_quick_sort (vector<int>& data, int low, int high) {
    int pivot = data[low];
    int pivotPos = low;
    for (int i = low + 1; i < high; i++) {
        if (data[i] < pivot) {
            swap(data[i], data[++pivotPos]);
        }
    }
    swap(data[low], data[pivotPos]);
    return pivotPos;
}

void quick_sort(vector<int>& data) {
    int low = 0, high = data.size();
    queue<pair<int, int>> posQueue;
    posQueue.push(make_pair(low, high));
    while (!posQueue.empty()) {
        pair<int, int> current = posQueue.front();
        posQueue.pop();
        int current_low = current.first;
        int current_high = current.second;
        if (current_low < current_high) {
            int pivot = part_quick_sort(data, current_low, current_high);
            posQueue.push(make_pair(current_low, pivot - 1));
            posQueue.push(make_pair(pivot + 1, current_high));
        }
    }
}

int main() {
    vector<int> data = {5, 7, 8, 2, 3, 6, 4, 9, 1};
    quick_sort(data);
    for (int i : data)
        cout << i << " ";
    return 0;
}