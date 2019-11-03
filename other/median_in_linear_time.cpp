#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

unsigned int NextRand24(unsigned int& cur, unsigned int a_gen, unsigned int b_gen) {
    cur = cur * a_gen + b_gen;
    return cur >> 8u;
}

unsigned int NextRand32(unsigned int& cur, unsigned int a_gen, unsigned int b_gen) {
    unsigned int first = NextRand24(cur, a_gen, b_gen);
    unsigned int second = NextRand24(cur, a_gen, b_gen);
    return (first << 8u) ^ second;
}

void GenerateArray(vector<unsigned int>& array) {
    size_t size;
    unsigned int cur = 0, a_gen, b_gen;
    cin >> size >> a_gen >> b_gen;
    array.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        array.emplace_back(NextRand32(cur, a_gen, b_gen));
    }
}

size_t Partition(vector<unsigned int>& array, unsigned int pivot) {
    int left = -1, right = array.size();
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
        std::swap(array[left], array[right]);
    }
    return right;
}

unsigned int FindOrderStatistics(vector<unsigned int>& array, size_t index) {
    while (array.size() > 10) {
        vector<unsigned int> medians_of_fives;
        for (size_t i = 0; i < array.size(); i += 5) {
            std::sort(array.begin() + i, array.begin() + i + std::min(5ul, array.size() - i));
            if (i + 2 < array.size()) {
                medians_of_fives.push_back(array[i + 2]);
            }
        }
        unsigned int pivot = FindOrderStatistics(medians_of_fives, medians_of_fives.size() / 2);
        size_t partition_index = Partition(array, pivot);
        if (index <= partition_index) {
            array.erase(array.begin() + partition_index + 1, array.end());
        } else {
            array.erase(array.begin(), array.begin() + partition_index + 1);
            index -= partition_index + 1;
        }
    }
    std::sort(array.begin(), array.end());
    return array[index];
}

int64_t CalcDistances(const vector<unsigned int>& array, unsigned int median) {
    int64_t sum = 0;
    for (unsigned int number : array) {
        if (number > median) {
            sum += number - median;
        } else {
            sum += median - number;
        }
    }
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
#endif
    vector<unsigned int> array;
    GenerateArray(array);
    vector<unsigned int> saved_array = array;
    unsigned int median = FindOrderStatistics(array, array.size() / 2);
    cout << CalcDistances(saved_array, median) << "\n";
    return 0;
}
