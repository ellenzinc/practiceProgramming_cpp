#include <iostream>
#include <utility>

using namespace std;

int count2sAtDigit(int number, int power) {
    int nextPower = power * 10;
    int right = number % power;
    
    int roundDown = number - number % nextPower;
    int roundUp = roundDown + nextPower;

    int digit = (number / power) % 10;
    if (digit < 2) {
        return roundDown / 10;
    } else if (digit == 2) {
        return roundDown / 10 + right + 1;
    } else {
        return roundUp / 10;
    }

}

int count2sInRange(int number) {
    int len = to_string(number).length();
    int res = 0;
    int powers = 1;
    for (int i = 0; i < len; i++) {
        res += count2sAtDigit(number, powers);
        powers *= 10;
    }
    return res;
}


int main() {
    int num1 = 2;
    int num2 = 12;
    int num3 = 512;
    int num4 = 61523;
    cout << "Number of ones in "<< num1 << " is "<< count2sInRange(num1) << endl;
    cout << "Number of ones in "<< num2 << " is "<< count2sInRange(num2) << endl;
    cout << "Number of ones in "<< num3 << " is "<< count2sInRange(num3) << endl;
    cout << "Number of ones in "<< num4 << " is "<< count2sInRange(num4) << endl;
    return 0;
}
