#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct NumberAndIndex {
    int number;
    size_t index;
};

bool operator<(const NumberAndIndex& first, const NumberAndIndex& second) {
    return first.number < second.number;
}


class MinSegmentTree {
public:
    explicit MinSegmentTree(size_t size) {
        size_ = 1 << static_cast<int>(std::ceil(std::log2(size)));
        array_.resize(2 * size_, {kDefaultValue, 0});
    }

    void Update(size_t index, int new_value = kDefaultValue) {
        size_t node = index + size_;
        array_[node] = {new_value, index};
        node /= 2;
        while (node > 0) {
            array_[node] = std::min(array_[node + node], array_[node + node + 1]);
            node /= 2;
        }
    }

    NumberAndIndex GetMin() {
        return array_[1];
    }

private:
    size_t size_;
    vector<NumberAndIndex> array_;
    static const int kDefaultValue = 2'000'000'000;
};

void ReadArrays(vector<vector<int>>& arrays) {
    size_t num_arrays, length;
    cin >> num_arrays >> length;
    arrays.resize(num_arrays);
    for (size_t i = 0; i < num_arrays; ++i) {
        vector<int>& array = arrays[i];
        array.resize(length);
        for (size_t j = 0; j < length; ++j) {
            cin >> array[j];
        }
    }
}

void PrintAnswer(const vector<int>& answer) {
    for (int number : answer) {
        cout << number << " ";
    }
    cout << "\n";
}

void MergeArrays(vector<vector<int>>& arrays, vector<int>* answer) {
    size_t num_arrays = arrays.size();
    size_t length = arrays[0].size();
    MinSegmentTree segment_tree(num_arrays);
    vector<size_t> pointer(num_arrays, 0);
    for (size_t i = 0; i < num_arrays; ++i) {
        segment_tree.Update(i, arrays[i][0]);
    }
    for (size_t i = 0; i < num_arrays * length; ++i) {
        NumberAndIndex min_element = segment_tree.GetMin();
        int number = min_element.number;
        size_t index = min_element.index;
        segment_tree.Update(index);
        answer->push_back(number);
        ++pointer[index];
        if (pointer[index] < length) {
            segment_tree.Update(index, arrays[index][pointer[index]]);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
#endif
    vector<vector<int>> arrays;
    ReadArrays(arrays);
    vector<int> answer;
    MergeArrays(arrays, &answer);
    PrintAnswer(answer);
    return 0;
}
