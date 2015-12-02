#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void findSmallestK(priority_queue<int> &pq, vector<int> &array, int k) {
    for (int i = 0; i < k; i++) {
        pq.push(array[i]);
    }
    
    for (int i = k; i < array.size(); i++) {
        if (array[i] < pq.top()) {
            pq.pop();
            pq.push(array[i]);
        } 
    }
}

vector<int> smallestK(vector<int> array, int k) {
    if (k < 0) return vector<int>();
    if (k > array.size()) return array;
    priority_queue<int> pq;
    findSmallestK(pq, array, k);
    vector<int> res(&(pq.top()), &(pq.top())+ pq.size());
    reverse(res.begin(), res.end());
    return res;
}

ostream &operator<<(ostream &os, const vector<int> &nums) {
    for (int n : nums) {
        os << n << " ";
    }
    return os;
}

int main() {
    vector<int> array = {24,152,23,53,46,75,6,8,2,67};
    cout << smallestK(array, 4) << endl;
    return 0;
} 
