#include <iostream>
#include <vector>

using namespace std;

int makeChanges(int n, int *denom, int index, vector<vector<int> > & mem) {
    if (mem[n][index] > 0)
        return mem[n][index];

    if (index >= 3) 
        return 1;
    int ways = 0;
    for (int i = 0; i * denom[index] <= n; i++) {
        ways += makeChanges(n - i * denom[index], denom, index+1, mem);
    }
    mem[n][index] = ways;
    return ways;
}

int makeChanges(int n){
    int denom[4] = {25, 10, 5, 1};
    vector<vector<int> > mem(n+1, vector<int>(4, 0));
    return makeChanges(n, denom, 0, mem);
}

int main() {
    cout << makeChanges(5) << endl;
    return 0;
}
