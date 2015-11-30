#include <iostream>
#include <vector>

using namespace std;

int findStartRight(const vector<int> &nums) {
    int n = nums.size();
    for (int i = n-2; i >= 0; i--) {
        if (nums[i] > nums[i+1]) {
            return i+1;
        }
    }
    return 0;
}

int findEndLeft(const vector<int> &nums) {
    int n = nums.size();
    for (int i = 1; i < n; i++) {
        if (nums[i] < nums[i-1]) {
            return i-1;
        }
    }
    return n-1;
}

int shrinkLeft(const vector<int> &nums, int minIndex, int endLeft) {
    int minValue = nums[minIndex];
    for (int i = endLeft; i >= 0; i--) {
        if (nums[i] <= minValue) 
            return i+1;
    }
    return 0;
}

int shrinkRight(const vector<int> &nums, int maxIndex, int startRight) {
    int maxValue = nums[maxIndex];
    for (int i = startRight; i < nums.size(); i++) {
        if (nums[i] >= maxValue)
            return i-1;
    }
    return nums.size() - 1;
}


void findUnsortedSequence(const vector<int> &nums) {
    int endLeft = findEndLeft(nums);
    if (endLeft == nums.size()-1) return; // already sorted
    int startRight = findStartRight(nums);

    int maxIndex = endLeft, minIndex = startRight;
    for (int i = endLeft + 1; i < startRight; i++) {
        if (nums[i] > nums[maxIndex]) maxIndex = i;
        if (nums[i] < nums[minIndex]) minIndex = i;
    }
    
    int leftIndex = shrinkLeft(nums, minIndex, endLeft);
    int rightIndex = shrinkRight(nums, maxIndex, startRight);
    cout << "Should sort values from " << leftIndex << " to "<< rightIndex << endl;
}

int main() {
    vector<int> nums = {1,2,4,7,10,11,7,12,6,7,16,18,19};
    cout << "start of right " << findStartRight(nums) << endl;
    cout << "end of left "<< findEndLeft(nums) << endl;
    findUnsortedSequence(nums);

    nums = {1,2,3,5,4};
    findUnsortedSequence(nums);
    
    return 0;
}
