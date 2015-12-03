#include <iostream>
#include <vector>

using namespace std;

class SubMatrix {
public:
    int row1;
    int row2;
    int col1;
    int col2;
    int sum;
    SubMatrix(int r1, int r2, int c1, int c2, int s): row1(r1), row2(r2), col1(c1), col2(c2), sum(s) {}
};

class Range{
public:
    int start = 0;
    int end = 0;
    int sum = 0;
    Range(int st, int e, int s): start(st), end(e), sum(s) {}
};

ostream &operator<<(ostream &os, const Range &r) {
    os << "start = "<< r.start << "; end = "<< r.end << "; sum = "<< r.sum << endl;
    return os;
}

ostream &operator<<(ostream &os, const SubMatrix &sm) {
    os << "("<< sm.row1 << ", "<< sm.col1 << ") -> (" << sm.row2 << ", " <<  sm.col2 << ") sum = " << sm.sum << endl;
    return os;
}

Range maxSubArraySum(vector<int> &partialSum) {
    Range res(0, 0, 0);
    int sum = 0;
    int start = 0;
    for (int i = 0; i < partialSum.size(); i++) {
        sum += partialSum[i];
        if (res.sum < sum) {
            res.start = start;
            res.end = i;
            res.sum = sum;
        }
        if (sum < 0) {
            sum = 0;
            start = i+1;
        }
    }
    return res;
}

SubMatrix findMaxSubmatrix(vector<vector<int> > &matrix) {
    SubMatrix res(0, 0, 0, 0, 0);
    int m = matrix.size();
    if (m == 0) return res;
    int n = matrix[0].size();

    for (int rowStart = 0; rowStart < m; rowStart++) {
        vector<int> partialSum(n, 0);
        for (int rowEnd = rowStart; rowEnd < m; rowEnd++) {
            for (int colIdx = 0; colIdx< n; colIdx++) 
                partialSum[colIdx] += matrix[rowEnd][colIdx];
            
            Range sumRange = maxSubArraySum(partialSum);
            if (sumRange.sum > res.sum) {
                res = SubMatrix(rowStart, rowEnd, sumRange.start, sumRange.end, sumRange.sum);
            }
        }
    }
    return res;
}

int main() {
    vector<vector<int> > matrix = {{9, -8, 1, 3, -2}, {-3, 7, 6, -2, 4}, {6, -4, -4, 8, -7}};
    cout << findMaxSubmatrix(matrix) << endl;
    //    vector<int> partialSum = {2,-2,5,-6,5,5,8};
    //Range bestRange = maxSubArraySum(partialSum);
    //cout << bestRange << endl;
    return 0;
}


