#include <iostream>
#include <vector>

using namespace std;

using htwt = pair<int, int>;

ostream &operator<<(ostream &os, const vector<htwt>& hw);
ostream &operator<<(ostream &os, const vector<vector<htwt> > &hw);

int binarySearch(vector<vector<htwt> > &buffer, int val) {
    int low = 0, high = buffer.size()-1;
    int res;
    while(low <= high) {
        int mid = low + ((high - low) >> 1);
        if (buffer[mid].back().second < val) {
            res = mid;
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return res+1;
}

vector<htwt> 
longestIncreasingSubsequence(vector<htwt> &hw) {
    sort(hw.begin(), hw.end(), 
         [](const htwt &a1, const htwt &a2) {
             return a1.first < a2.first;});
    vector< vector<htwt> > buffer;

    for (int i = 0; i < hw.size(); i++) {
        if (buffer.empty()) {
            buffer.push_back(vector<htwt>(1,hw[i]));
        } else if (buffer[0][0].second >= hw[i].second) { 
            buffer[0][0] = hw[i];
        } else if (buffer.back().back().second <= hw[i].second) {
            vector<htwt> tmp = buffer.back();
            tmp.push_back(hw[i]);
            buffer.push_back(tmp);
        } else {
            buffer[binarySearch(buffer, hw[i].second)].back() = hw[i];
        }
        
        // commented print out
        // cout << "i = "<< i << ": " << endl;
        // cout << "buffer = " << endl <<  buffer; 
    }
    
    return buffer.back();
}

ostream &operator<<(ostream &os, const vector<htwt>& hw) {
    for (int i = 0; i < hw.size(); i++) {
        os << "(" << hw[i].first << ", " << hw[i].second << ")" << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const vector<vector<htwt> > &hw) {
    for (int i = 0; i < hw.size(); i++) {
        os << hw[i] << endl;
    }
    return os;
}

int main() {
    vector<htwt> hw = {{152, 42}, {150, 64}, {165, 52}, {175, 60}, {172, 80}};
    cout << longestIncreasingSubsequence(hw) << endl;
    return 0;
}
