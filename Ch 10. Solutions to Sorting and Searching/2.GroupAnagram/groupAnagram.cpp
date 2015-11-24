#include <iostream>
#include <vector>
#include <string>

using namespace std; 

void sortAnagram(vector<string> &strs) {
    sort(strs.begin(), strs.end(), [](const string &a, const string &b) {
		string s1 = a, s2 = b;
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());
		return s1 < s2;
	  });

}

// print the vector
template<typename T>
ostream& operator<< (ostream &os, const vector<T> &vec) {
    for (int i = 0; i < vec.size(); i++) {
	  os << vec[i] << " ";
    }
	return os;
}

int main() {
    vector<string> strs = {"stop", "store", "start", "art", "dart", "tard", "ardt", "tops"};
    sortAnagram(strs);
	cout << strs << endl;
	vector<string> strs2 = {"a", "b", "cb", "bc", "abc", "cba", "ccc"};
	sortAnagram(strs2);
	cout << strs2 << endl;
    return 0;
}
