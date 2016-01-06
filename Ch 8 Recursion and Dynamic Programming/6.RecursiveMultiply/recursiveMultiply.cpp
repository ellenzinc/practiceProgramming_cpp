#include <iostream>

using namespace std;

long multiplyHelper(int smaller, int larger) {
    if (smaller == 0)
        return 0;
    if (smaller == 1)
        return larger;
    
    long half = multiplyHelper(smaller/2, larger);
    long res = half + half;
    if (smaller % 2)
        res += larger;
    return res;
}

long multiply(int a, int b) {
    if (a > b)
        swap(a, b);
    return multiplyHelper(a, b);
}

int main() {
    cout << multiply(12, 12) << endl;
    cout << multiply(INT_MAX, 0) << endl;
    cout << multiply(INT_MAX, INT_MAX) << endl;
    return 0;
}
