#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

ostream &operator<<(ostream& os, const vector<int> &vec) {
    for (int v : vec) {
        os << v << " ";
    }
    return os;
}

vector<int> findDeltas(const string &s) {
    vector<int> result(s.size(), 0);
    int delta = 0;
    for (int i = 0; i < s.size(); i++) {
        if (isalpha(s[i])) {
            delta++;
        } else {
            delta--;
        }
        result[i] = delta;
    }
    return result;
}

string findSubarray(vector<int> &deltas, const string &s) {
    unordered_map<int, int> delta2Count;
    int index[2] = {0, -1};
    int maxLength = 0;
    for (int i = 0; i < deltas.size(); i++) {
        if (delta2Count.count(deltas[i])) {
            if (i - delta2Count[deltas[i]] + 1 > maxLength) {
                maxLength = i - delta2Count[deltas[i]] + 1;
                index[0] = delta2Count[deltas[i]]+1;
                index[1] = i;
            }
        } else {
            delta2Count[deltas[i]] = i;
        }
    }
    return s.substr(index[0], index[1] - index[0] + 1);
}

string findLongestSubarray(const string &s) {
    if (s.empty()) return "";
    vector<int> deltas = findDeltas(s);
    cout << deltas << endl;
    return findSubarray(deltas, s);
}

int main() {
    cout << findLongestSubarray("aAbB12C11CB3he4dgesf") << endl;
}
