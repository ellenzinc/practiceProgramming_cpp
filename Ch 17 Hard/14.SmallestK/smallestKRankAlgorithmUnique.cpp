#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int partition(vector<int> &nums, int start, int end, int pivot) {
    int prevIdx = start;
    for (int i = start; i < end; i++) {
        if (nums[i] < pivot) {
            swap(nums[i], nums[prevIdx++]);
        } 
    }
    swap (nums[end], nums[prevIdx]);
    return prevIdx;
}

int findKthValue(vector<int> &array, int k, int start, int end) {
    int pivot = array[end];
    int leftEnd = partition(array, start, end, pivot);
    int leftSize = leftEnd - start + 1;
    if (k == leftSize) {
        return leftEnd;
    } else if (k > leftSize) {
        return findKthValue(array, k-leftSize, leftEnd+1, end);
    } else {
        return findKthValue(array, k, start, leftEnd-1);
    }
}

ostream &operator<<(ostream &os, const vector<int> &vec);
vector<int> smallestK(vector<int> array, int k) {
    if (k <= 0) return vector<int>();
    if (k > array.size()) return array;
    
    int n = array.size();
    // int idx = n;
    findKthValue(array, k, 0, n-1);
    //    for (int i = k; i >= 2; i--) {
    //    idx = findKthValue(array, i, 0, idx-1);
    //    cout << array << endl;
    //}
    vector<int> res(array.begin(), array.begin() + k);
    return res;
}

ostream &operator<<(ostream &os, const vector<int> &vec) {
    for (int val : vec) {
        os << val << " ";
    }
    return os;
}

int main() {
    vector<int> array = {24,152,23,53,46,75,6,8,2,67,123,24, 35 ,64, 323, 234,12, 24, 2, 4};
    cout << smallestK(array, 15) << endl;
    return 0;
} 
