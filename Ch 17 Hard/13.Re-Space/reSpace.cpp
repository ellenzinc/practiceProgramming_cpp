#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>


using namespace std;

class ParseResult {
public:
    int invalid  = INT_MAX;
    string parsed;
    ParseResult() {}
    ParseResult(int inv, string p) : invalid(inv), parsed(p) {} 
};

void printMemo(const vector<ParseResult> &memo) {
    for (int i = 0; i < memo.size(); i++) {
        cout <<"\"" << memo[i].parsed << "\"" << " has "<< memo[i].invalid << " invalid chars." << endl;
    }
    cout << endl;
}

ParseResult split(const unordered_set<string> &dict, string &sentence, int start, vector<ParseResult> &memo) {
    if (start >= sentence.length()) 
        return ParseResult(0, "");
    if (memo[start].invalid != INT_MAX)
        return memo[start];
    string cur;
    int bestInvalid = INT_MAX;
    string bestSplit;
    for (int i = start; i < sentence.size(); i++){
        cur += sentence[i];
 
        int invalid = (dict.count(cur) == 0 ? cur.length() : 0);
        if (invalid < bestInvalid) {
            ParseResult next = split(dict, sentence, i+1, memo);
            if (bestInvalid > next.invalid + invalid) {
                bestInvalid = next.invalid + invalid;
                bestSplit = cur + ' ' +  next.parsed;
                if (bestInvalid == 0) break;
            }
        }
    }
    memo[start] = ParseResult(bestInvalid, bestSplit);
    printMemo(memo);
    return memo[start];
}

string bestSplit(const unordered_set<string> &dictionary, string &sentence) {
    vector<ParseResult> memo(sentence.size());
    ParseResult r = split(dictionary, sentence, 0, memo);
    return r.parsed;
}

int main() {
    unordered_set<string> dict = {"this", "is", "favorite", "food"};
    string sentence = "thisismikesfavoritefood";
    cout << bestSplit(dict, sentence) << endl;
    return 0;
}
