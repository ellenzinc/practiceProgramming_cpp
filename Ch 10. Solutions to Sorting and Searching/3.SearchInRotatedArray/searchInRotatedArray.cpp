#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


int searchInRotatedArray(vector<int> &nums, int target){
    if (nums.empty())
        return -1;
    int low = 0, high = nums.size()-1;

    while(low <= high) {
        int mid = low + ((high-low) >> 1);
        if (nums[mid] == target) return mid;
        if (nums[mid] < nums[low]) {
            if (target > nums[mid] && target <= nums[high]) {
                low = mid+1;
            } else {
                high = mid-1;
            }
        } else if (nums[mid] > nums[low]) {
            if (target >= nums[low] && target < nums[mid]) {
                high = mid-1;
            } else{
                low = mid+1;
            }
        } else {
            if(target > nums[mid])
                low++;
            else
                high--;
        }
    }
    return -1;
}


int main() {
    vector<int> nums = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    assert(searchInRotatedArray(nums, 5) == 8);
    return 0;
}
