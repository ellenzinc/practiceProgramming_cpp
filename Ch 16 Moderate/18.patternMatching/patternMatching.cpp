#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

bool matches(const string &pattern, const string &value, int mainSize, int altSize, int altIndex) {
    int valueIndex = mainSize;
    for (int i = 1; i < pattern.size(); i++) {
        int curSize = pattern[i] == pattern[0] ? mainSize : altSize;
        int offset = pattern[i] == pattern[0] ? 0 : altIndex;
        
        if (value.compare(offset, curSize, value, valueIndex, curSize) != 0) 
            return false;
        valueIndex += curSize;
    }
    return true;
}

bool doesMatch(const string &pattern, const string &value) {
    if (pattern.empty()) return value.empty();
    
    char mainChar = pattern[0];
    char alterChar = mainChar == 'a' ? 'b' : 'a';

    int countMain = count(pattern.begin(), pattern.end(), mainChar);
    int countAlter = pattern.size() - countMain;
    size_t tmp = pattern.find_first_of(alterChar);
    int firstAlter = tmp == string::npos ? pattern.size() : tmp;


    int n = value.size();
    
    int maxMainSize = n / countMain;

    for (int i = 0; i <= maxMainSize; i++) {
        int remainingLength = n - i * countMain;
        int altIndex, altSize;
        if (countAlter == 0 || remainingLength % countAlter == 0) {
            int altIndex = firstAlter * i;
            int altSize = countAlter == 0 ? 0 : remainingLength / countAlter;

            if (matches(pattern, value, i, altSize, altIndex)) 
                return true;
        }
    }
    return false;
}

int main() {
    cout << doesMatch("aabab", "catcatgocatgo") << endl;
    cout << doesMatch("abab", "getupgetup") << endl;
    cout << doesMatch("aaabb", "catcatgo") << endl;
}
