#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Person {
public:
    int birth;
    int death;
    Person(int b, int d): birth(b), death(d) {}
};

int findMaxAliveYear(vector<Person> &people, int minYear, int maxYear) {
    int maxAliveYear = minYear, maxAlive = 0;
    map<int, int> deltas;
    for (Person& person : people) {
        deltas[person.birth]++;
        deltas[person.death+1]--;
    }
    int cumulative = 0;
    for (auto it = deltas.begin(); it != deltas.end(); it++) {
        cumulative += it->second;
        if (cumulative > maxAlive) {
            maxAlive = cumulative;
            maxAliveYear = it->first;
        }
    }
    return maxAliveYear;
}

int main() {
    vector<Person> people = {Person(12, 15), Person(20, 90), Person(10, 98), Person(1, 72), Person(10, 98), Person(23, 82), Person(13, 98), Person(83, 99), Person(75, 94)};
    cout << "Max Alive Year = " << findMaxAliveYear(people, 0, 100) << endl;
    
    vector<Person> people2 = {Person(12, 15), Person(20, 90), Person(30, 32)};
    cout << "Max Alive Year = " << findMaxAliveYear(people2, 0, 100) << endl;
    return 0;
}
