#include <bits/stdc++.h>
using namespace std;

size_t partition(vector<int>& array, int pivot) {
    int left = -1;
    int right = array.size();
    while (left < right) {
        do {
            ++left;
        } while (array[left] < pivot);
        do {
            --right;
        } while (array[right] > pivot);
        if (left >= right) {
            break;
        }
        swap(array[left], array[right]);
    }
    return right;
}

int order_statistics(vector<int>& array, int index) {
    while (array.size() > 10) {
        vector<int> medians_of_fives;
        for (int i = 0; i < array.size(); i += 5) {
            sort(array.begin() + i, array.begin() + i + min(5, int(array.size()) - i));
            if (i + 2 < array.size()) {
                medians_of_fives.push_back(array[i + 2]);
            }
        }
        int pivot = order_statistics(medians_of_fives, medians_of_fives.size() / 2);
        int partition_index = partition(array, pivot);
        if (index <= partition_index) {
            array.erase(array.begin() + partition_index + 1, array.end());
        } else {
            array.erase(array.begin(), array.begin() + partition_index + 1);
            index -= partition_index + 1;
        }
    }
    sort(array.begin(), array.end());
    return array[index];
}

int main() {
    return 0;
}
