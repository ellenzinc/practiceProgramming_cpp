#include <iostream>
#include <string>
#include <vector>
using namespace std;

int sparseSearch(const vector<string> &strs, const string &target) {
    if (strs.empty() || target.empty()) return -1;
    int left = 0, right = (int)strs.size()-1;
    while(left <= right) {
        int mid= left + ((right - left)>>1);
        
        if (!strs[mid].empty()) {
            if (strs[mid] == target) return mid;
            
            if (strs[mid] < target) 
                left = mid+1;
            else
                right = mid-1;
        } else {
            if (strs[left] == target) return left;
            if (strs[right] == target) return right;

            if (!strs[left].empty() && strs[left]< target) 
                left++;
            else
                right--;
        }
        
    }
    cout << "left = "<< left << "; right = " << right << ";" << endl;}

int main () {
    cout << sparseSearch({"at", "", "", "", "ball","", "", "car", "", "", "dad", "", ""}, "dad") << endl;
    
    return 0;
}
