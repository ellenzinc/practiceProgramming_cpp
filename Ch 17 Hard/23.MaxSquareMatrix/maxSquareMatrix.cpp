#include <iostream>
#include <vector>

using namespace std;

class SubSquare {
public:
    int row = -1;
    int col = -1;
    int size = 0;
    SubSquare(){}
    SubSquare(int r, int c, int s): row(r), col(c), size(s) {}
};

ostream &operator<<(ostream &os, const SubSquare &ss) {
    os << "row = "<< ss.row << "; col = "<< ss.col << "; size = " << ss.size << endl;
    return os;
}

class SquareCell {
public:
    int blackRight = 0;
    int blackBelow = 0;
    SquareCell(){}
    SquareCell(int r, int b): blackRight(r), blackBelow(b){}
};

ostream &operator<<(ostream &os, const vector<vector<SquareCell> > &res) {
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[0].size(); j++) {
            os << "(" << res[i][j].blackRight << ", "<< res[i][j].blackBelow << ")" << " ";
        }
        cout << endl;
    }
    return os;
}

vector<vector<SquareCell> > 
preprocessing(vector<vector<char> > &matrix) {
    vector<vector<SquareCell> > res;
    if (matrix.empty()) return res;
    int m = matrix.size();
    int n = matrix[0].size();

    res = vector<vector<SquareCell> >(m, vector<SquareCell>(n));
    for (int i = m-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            if (matrix[i][j] == 'B') {
                res[i][j].blackRight++;
                res[i][j].blackBelow++;
                if (j < n-1) 
                    res[i][j].blackRight += res[i][j+1].blackRight;
                if (i < m-1) 
                    res[i][j].blackBelow += res[i+1][j].blackBelow;
            }
        }
    }
    return res;
} 

bool isSquare(vector<vector<SquareCell> > &preprocessed, int row, int col, int size) {
    SquareCell *topLeft = &preprocessed[row][col];
    SquareCell *topRight = &preprocessed[row][col+size-1];
    SquareCell *bottomLeft = &preprocessed[row+size-1][col];

    if (topLeft->blackRight < size || topLeft->blackBelow < size ||
        topRight->blackBelow < size || bottomLeft->blackRight < size)
        return false;
    return true;
}

SubSquare findSquare(vector<vector<SquareCell> > &preprocessed, int size) {
    int len = preprocessed.size() - size + 1;
    for (int row = 0; row < len; row++) {
        for (int col = 0; col < len; col++) {
            if (isSquare(preprocessed, row, col, size)) 
                return SubSquare(row, col, size);
        }
    }
    return SubSquare();
}

SubSquare findSquare(vector<vector<char> > &matrix) {
    vector<vector<SquareCell> > preprocessed = preprocessing(matrix);
    cout << preprocessed << endl;
    int bestSize = 0;
    SubSquare ss;
    for (int i = matrix.size(); i >= 1; i--) {
        ss = findSquare(preprocessed, i);
        if (ss.size > 0)
            return ss;
    }
    return ss;
}

int main() {
    vector<vector<char> > matrix = {{'W', 'B', 'W'}, {'B', 'B', 'W'}, {'B', 'B', 'W'}};
    cout << findSquare(matrix);
    return 0;
}
