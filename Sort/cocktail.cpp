#include <iostream>
#include <vector>

using namespace std;

void cocktail_sort(vector<int>& data) {
    int high;
    int start = 0, end = data.size()- 1;
    do {
        high = 0;
        for (int i = start; i < end; i++) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                high = i;
            }
        }
        end = high;
        for (int j = end; j > start; j--) {
            if (data[j] < data[j - 1]) {
                swap(data[j], data[j - 1]);
                high = j;
            }
        }
        start = high;
    } while (high);
}

int main() {
    vector<int> data = {5, 7, 8, 2, 3, 6, 4, 9, 1};
    cocktail_sort(data);
    for (int i : data)
        cout << i << " ";
    return 0;
}