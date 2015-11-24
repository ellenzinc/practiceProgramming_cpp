#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

void peakAndValley(vector<int> &nums) {
    if (nums.size() <= 1) return;
    for (int i = 1; i < nums.size(); i++) {
        if ((i % 2 && nums[i] > nums[i-1]) || (i % 2 == 0 && nums[i] < nums[i-1])){
            swap(nums[i], nums[i-1]);
        } 
    }
}


int main() {
    vector<int> nums = {9, 1, 0, 4, 8, 7};
    peakAndValley(nums);
    for (int i = 1; i < nums.size()-1; i++) {
        if (i % 2) 
            assert(nums[i-1] >= nums[i]  && nums[i]<= nums[i+1]);
        else 
            assert(nums[i-1] <= nums[i] && nums[i] >= nums[i+1]);
    }
}
