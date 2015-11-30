#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;

int rangeRand(int low, int high, unsigned int seed) {
    default_random_engine generator;
    generator.seed(seed);
    uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}

void shuffleArray(vector<int> &nums) {
    unsigned int seed = time(NULL);
    for (int i = 0; i < nums.size(); i++) {
        int k = rangeRand(0, i, seed);
        swap(nums[k], nums[i]);
    }
}

ostream &operator<<(ostream &os, const vector<int> &vec) {
    for (int v : vec)
        os << v << " ";
    return os;
}

int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};
    cout << "Before Shuffling: "<< nums << endl;
    shuffleArray(nums);
    cout << "After Shuffling: " << nums << endl;
}
