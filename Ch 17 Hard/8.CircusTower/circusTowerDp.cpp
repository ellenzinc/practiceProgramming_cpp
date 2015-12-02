#include <iostream>
#include <vector>

using namespace std;

using htwt = pair<int, int>;

bool canAppend(vector<htwt> &vec, htwt &val) {
    if (vec.back().first < val.first && vec.back().second < val.second )
        return true;
    return false;
}

void bestSequenceAtIndex(vector<vector<htwt> > &dp, int pos, vector<htwt> &hw) {
    int bestIdx = -1;
    int bestSize = 0;
    htwt val = hw[pos];
    for (int i = 0; i < dp.size(); i++) {
        if (canAppend(dp[i], val)) {
            if (dp[i].size() > bestSize) {
                bestSize = dp[i].size();
                bestIdx = i;
            }
        }
    }
    
    vector<htwt> bestSequence;
    if (bestIdx >= 0) 
        bestSequence = dp[bestIdx];
    bestSequence.push_back(val);
    dp.push_back(bestSequence);
}

vector<htwt> 
longestIncreasingSubsequence(vector<htwt> &hw) {
    sort(hw.begin(), hw.end(), 
         [](const htwt &a1, const htwt &a2) {
             return a1.first < a2.first;});
    vector<vector<htwt> > dp;
    vector<htwt> bestSequence;

    for (int i = 0; i < hw.size(); i++) {
        bestSequenceAtIndex(dp, i, hw);
        if (dp.back().size() > bestSequence.size()) {
            bestSequence = dp.back();
        }
    }
    
    return bestSequence;
}

ostream &operator<<(ostream &os, const vector<htwt>& hw) {
    for (int i = 0; i < hw.size(); i++) {
        os << "(" << hw[i].first << ", " << hw[i].second << ")" << endl;
    }
    return os;
}

int main() {
    vector<htwt> hw = {{152, 42}, {150, 64}, {165, 52}, {175, 60}, {172, 80}};
    cout << longestIncreasingSubsequence(hw) << endl;
    return 0;
}
