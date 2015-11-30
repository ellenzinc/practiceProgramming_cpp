#include <iostream>
#include <vector>

using namespace std;

void printPond(const vector< vector<int> > &pond) {
    for (int i = 0; i < pond.size(); i++) {
        for (int j = 0; j < pond[0].size(); j++) {
            cout << pond[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void findPondSize(vector<vector<int> > &pond, int xPos, int yPos, int &pondSize) {
    int m = pond.size(), n = pond[0].size();
    for (int i = max(xPos-1, 0); i <= min(xPos+1, m-1); i++) {
        for (int j = max(yPos-1, 0); j <= min(yPos+1, n-1); j++) {
            if ((i != xPos || j != yPos) && pond[i][j] == 0) {
                pond[i][j] = 1;
                pondSize++;
                findPondSize(pond, i, j, pondSize);
            }
        }
    }
}

vector<int> computePondSizes(vector<vector<int> > &pond) {
    vector<int> res;
    if (pond.empty()) return res;
    for(int i = 0; i < pond.size(); i++) {
        for (int j = 0; j < pond[0].size(); j++) {
            if (pond[i][j] == 0) {
                pond[i][j] = 1;
                int pondSize = 1;
                findPondSize(pond, i, j, pondSize);
                res.push_back(pondSize);
            } 
        }
    }
    return res;
}

void printVector(const vector<int> &vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<int> > pond  = { {0, 2, 1, 0}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1} };
    printPond(pond);
    printVector(computePondSizes(pond));
    
    return 0;
}
