#include <iostream>
#include <vector>

using namespace std;

pair<int, int> findElementUtility(const vector<vector<int> > &matrix, int target, 
                                  int x1, int y1, int x2, int y2)
{
    // find the diagonal line to split;
    if (x1 > x2 || y1 > y2) return make_pair(-1, -1);
    if (x1 == x2 && y1 == y2) 
        if (matrix[x1][y1] == target)
            return make_pair(x1, y1);
        else 
            return make_pair(-1, -1);

    // cout << "x1 = " << x1 << "; y1 = " << y1 << "; x2 = " << x2 << "; y2 = "<< y2 << endl; 

    int nRow = x2 - x1 + 1;
    int nCol = y2 - y1 + 1;
    int startX = x1, startY = y1;
    if (nRow > nCol) {
        startX += (nRow-nCol)/2;
    } else {
        startY += (nCol-nRow)/2;
    }

    int len = min(nRow, nCol);
    int low = 0, high = len-1;
    while(low <= high){
        int mid = (low + high) / 2;
        if (matrix[startX + mid][startY + mid] == target){
            return make_pair(startX+mid, startY+mid);
        } else if (matrix[startX+mid][startY+mid] < target) {
            low = mid+1;
        } else
            high = mid-1;
    }

    // cout << "low = "<< low << "; high = "<< high << endl;

    if (high >= 0 && low < len) {
        // cout << "(" << x1 << ", " << startY+high+1<< ") -> (" << startX+high << ", "<< y2 << ")" << endl;
        auto pair1 = findElementUtility(matrix, target, x1, startY+high+1, startX+high, y2);
        if (pair1.first >= 0) return pair1;
        
        
        //        cout << "(" << startX+low << ", "<< y1 << ") -> (" << x2 << ", " << startY+high << ") " << endl;
        auto pair2 = findElementUtility(matrix, target, startX+low, y1, x2, startY+high);
        if (pair2.first >= 0) return pair2;
        
    } else {
        if (high < 0){
            if (nRow < nCol) {
                return findElementUtility(matrix, target, x1, y1, startX, startY-1);
            } else {
                return findElementUtility(matrix, target, x1, y1, startX-1, startY);
            }
        }
               
        //        cout << "(" << startX+low << ", "<< startY+low << ") -> (" << x2 << ", " << y2 << ") " << endl;
        if (low == len) {
            if (nRow < nCol)
                return findElementUtility(matrix, target, x2, startY+len, x2, y2);
            else
                return findElementUtility(matrix, target, startX+len, y2, x2, y2);
        }

    }
    return make_pair(-1, -1);
}

pair<int, int> findElement(const vector< vector<int> > &matrix, int target) {
    pair<int, int> res = {1,1};
    int nRow = matrix.size(), nCol = matrix[0].size();
    return findElementUtility(matrix, target, 0, 0, nRow-1, nCol-1);
}


void test1() {
    vector< vector<int> > matrix = {{15,20,70,85}, {20,35,80,95}, {30,55,95,105}, {40,80,100,120}};
    int target = 85;
    auto res = findElement(matrix, target);
    cout << target << " is at Coordindate: (" << res.first << ", "<< res.second << ")." << endl;
    
    target = 120;
    res = findElement(matrix, target);
    cout << target << " is at Coordindate: (" << res.first << ", "<< res.second << ")." << endl;    

}

void test2() {
    vector< vector<int> > matrix = {{15,20,70,85}, {20, 35, 80, 95}};
    int target = 35;
    auto res = findElement(matrix, target);
    cout << target << " is at Coordinate: (" << res.first << ", "<< res.second << "). "<< endl;
    
    target = 20;
    res = findElement(matrix, target);
    cout << target << " is at Coordinate: (" << res.first << ", "<< res.second << "). "<< endl;
}


int main() {
    test1();
    cout << endl;
    test2();
    return 0;
}
