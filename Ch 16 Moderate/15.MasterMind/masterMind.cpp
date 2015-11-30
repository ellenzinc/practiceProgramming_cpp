#include <iostream>
#include <string>

using namespace std;

class Result {
    friend ostream& operator<< (ostream& os, const Result &res);
public:
    Result(int h, int p) : hits(h), pHits(p) {}
private:
    int hits = 0;
    int pHits = 0;
};

ostream& operator<< (ostream &os, const Result &res) {
    os << res. hits << " hits, " << res.pHits << " PseudoHits";
    return os;
}

size_t returnValue(char c) {
    switch(c) {
    case 'R': return 0;
    case 'Y': return 1;
    case 'G': return 2;
    case 'B': return 3;
    default: return 4;
    }
}

Result estimate(const string &secret, const string &guess) {
    int hits = 0, pHits = 0;
    if (guess.size() != secret.size()) return Result(0, 0);
    int g[4] = {0};
    int s[4] = {0}; 
    for (int i = 0; i < secret.size(); i++) {
        if (guess[i] == secret[i]) {
            hits++;
        } else {
            int gIdx = returnValue(guess[i]);
            int sIdx = returnValue(secret[i]);
            if (gIdx > 3 || sIdx > 3) return Result(0, 0);
            g[gIdx]++;
            s[sIdx]++;
        }
    }

    for (int i = 0; i < 4; i++) {
        pHits += min(g[i], s[i]);
    }
    return Result(hits, pHits);
}

int main() {
    cout << estimate("RGGB", "YRGB") << endl; // should return 2 Hits, 1 PHits
    cout << estimate("RGBY", "GGRR") << endl; // should return 1 Hit, 1 PHits
    return 0;
}
