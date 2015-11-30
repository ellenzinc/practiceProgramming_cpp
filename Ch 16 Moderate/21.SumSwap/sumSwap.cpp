#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>
//#include <functional>

using namespace std;

vector<int> findSwapValues(vector<int> &nums1, vector<int> &nums2) {
    vector<int> res;
    if (nums1.empty() || nums2.empty()) return res;

    int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
    int sum2 = accumulate(nums2.begin(), nums2.end(), 0);

    if ((sum1 - sum2) % 2) return res;

    unordered_set<int> dict(nums2.begin(), nums2.end());
    
    int diff = (sum1 - sum2) / 2;
    for (int val : nums1) {
        if (dict.count(val-diff)) 
            return vector<int>({val, val-diff});
    }
    return res;
}

void printVec(const vector<int> &vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums1 = {4,1,2,1,1,2};
    vector<int> nums2 = {3,6,3,3};

    printVec(findSwapValues(nums1, nums2));

    return 0;
}
