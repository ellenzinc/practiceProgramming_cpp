#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int majorityElement(const vector<int> &nums) {
    assert(!nums.empty());
    int majority = nums[0];
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (count == 0)
            majority = nums[i];

        if (nums[i] == majority)
            count++;
        else
            count--;         
    }
    count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == majority)
            count++;
    }
    return count > nums.size() / 2 ? majority : -1;
}


int main() {
    vector<int> nums = {3, 1, 7, 1, 1, 7, 7, 3, 7, 7, 7};
    cout << majorityElement(nums) << endl;
}
