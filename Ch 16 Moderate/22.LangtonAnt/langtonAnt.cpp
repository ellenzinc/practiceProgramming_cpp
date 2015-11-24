#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <utility>
#include <cstdlib>
using namespace std;

enum Orientation {LEFT, RIGHT, UP, DOWN};

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator () (const std::pair<T1,T2> &p) {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        
        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

class Ant {
    friend class Board;
public:
    void turn(bool clockwise) {
        switch(orient) {
            case LEFT : orient = clockwise ? UP : DOWN; break;
            case RIGHT: orient = clockwise ? DOWN : UP; break;
            case UP : orient = clockwise? RIGHT : LEFT; break;
            case DOWN: orient = clockwise? LEFT: RIGHT;
        }
    }
    
    void move() {
        switch (orient) {
            case LEFT: position.second--; break;
            case RIGHT: position.second++; break;
            case UP: position.first--; break;
            case DOWN: position.first++;
        }
    }
    
private:
    Orientation orient = RIGHT;
    pair<int, int> position = {0, 0};
};

class Board {
public:
    Board() {}
    void flip(const pair<int, int> &pos) {
        if (whites.find(pos) != whites.end()) {
            whites.erase(pos);
        } else {
            whites.insert(pos);
        }
    }
    
    void ensureFit(const pair<int, int> pos) {
        topLeft.first = min(pos.first, topLeft.first);
        topLeft.second = min(pos.second, topLeft.second);
        bottomRight.first = max(bottomRight.first, pos.first);
        bottomRight.second = max(bottomRight.second, pos.second);
    }
    
    void move() {
        ant.turn(whites.find(ant.position) != whites.end());
        flip(ant.position);
        ant.move();
        ensureFit(ant.position);
    }
    
    void printBoard(){
        for (int i = topLeft.first ; i <= bottomRight.first; i++) {
            for (int j = topLeft.second; j <= bottomRight.second; j++) {
                if (whites.find(make_pair(i,j))!= whites.end()) {
                    cout << "_";
                } else {
                    cout << "X";
                }
            }
            cout << endl;
        }
        cout << "Ant is at (" << ant.position.first << ", "<< ant.position.second <<") facing "<< ant.orient << endl;
    }
    
private:
    //set<pair<int, int>> whites;
    unordered_set<pair<int, int>, pair_hash> whites;
    pair<int, int> topLeft = {0, 0};
    pair<int, int> bottomRight = {0, 0};
    Ant ant;
};


int main(int argc, const char * argv[]) {
    Board bd;
    int N = 100;
    for (int i = 0; i < N; i++) {
        bd.move(); bd.printBoard();
        cout << endl;
    }
    //unordered_set<pair<int, int>, pair_hash> whites;

    return 0;
}