#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

ostream &operator<<(ostream &os, const unordered_map<string, bool> &memo) {
    for (auto it = memo.begin(); it != memo.end(); it++) {
        os << it->first << ": "<< it->second << endl;
    }
    return os;
}


bool issplittable(unordered_map<string, bool> &memo, vector<string> &str, int pos) {
    int n = str[pos].size();
    for (int i = n-1; i >= 1; i--) {
        if (memo.count(str[pos].substr(i)) && memo.count(str[pos].substr(0, i))){
            memo[str[pos]] = true;
            cout << memo << endl;
            return true;
        } 
    }
    memo[str[pos]] = false;
    cout << memo << endl;
    return false;
}

string printLongestWord(vector<string> &str) {
    string res;
    sort(str.begin(), str.end(), [](const string &a, const string &b) 
         {return a.length() < b.length(); });
    unordered_map<string, bool> memo;
    for (int i = 0; i < str.size(); i++) {
        if (issplittable(memo, str, i)) {
            res = str[i];
        }
    }
    return res;
}

int main() {
    vector<string> str = {"getup", "get", "up", "ketchup", "ketch", "ket", "ch"};
    cout << printLongestWord(str) << endl;    
    return 0;
}
