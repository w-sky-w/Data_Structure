#include <iostream>
#include <vector>

using namespace std;

void odd_even_sort(vector<int>& data) {
    if (data.size() <= 1)
        return;
    bool exchanged;
    int n = data.size();
    while(1) {
        exchanged = false;
        for (int i = 0; i + 1 < n; i += 2) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                exchanged = true;
            }
        }
        for (int j = 1; j + 1 < n; j += 2) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                exchanged = true;
            }
        }
        if (!exchanged)
            break;
    }
}

int main() {
    //vector<int> data = {5, 7, 8, 2, 3, 6, 4, 9, 1};
    vector<int> data = {5, 7, 8, 10, 3, 6, 4, 9, 1, 48};
    odd_even_sort(data);
    for (int i : data)
        cout << i << " ";
    return 0;
}