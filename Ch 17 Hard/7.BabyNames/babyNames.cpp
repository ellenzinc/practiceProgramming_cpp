#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Node {
public:
    unordered_set<int> neighbors;
    string s;
    int val;
    Node(const string &str, int v) : s(str), val(v) {}
};

class Graph {
public:
    Graph(){}
    Graph(unordered_map<string, int> & names) {
        for (auto it = names.begin(); it != names.end(); it++) {
            addNode(it->first, it->second);
        }
    }
    void addNode(const string &s, int val) {
        dict[s] = nodes.size();
        nodes.push_back(Node(s, val));
    }

    void connectEdges(vector<vector<string> > &synonyms) { 
        for (int i = 0; i < synonyms.size(); i++) {
            int idx1 = dict[synonyms[i][0]];
            int idx2 = dict[synonyms[i][1]];
            nodes[idx1].neighbors.insert(idx2);
            nodes[idx2].neighbors.insert(idx1);
        }
    }

    void printGraph() {
        for (int i = 0; i < nodes.size(); i++) {
            cout << nodes[i].s << ": ";
            for (int neighbor : nodes[i].neighbors) {
                cout << nodes[neighbor].s << " "; 
            }
            cout << endl;
        }
        cout << endl;
    }

    void mergeRecord(unordered_map<string, int> &res) {
        vector<bool> visited(nodes.size(), false);
        for (int i = 0; i < nodes.size(); i++) {
            if (!visited[i]) {
                int val = getComponentValue(i, visited);
                res[nodes[i].s] = val; 
            }
        }
    }

    int getComponentValue(int i, vector<bool> &visited) {
        if (visited[i]) return 0;
        visited[i] = true;
        int sum = nodes[i].val;
        for (int idx : nodes[i].neighbors) {
            if (!visited[idx]) {
                sum += getComponentValue(idx, visited);
            }
        }
        return sum;
    }
private:
    vector<Node> nodes;
    unordered_map<string, int> dict;
};

unordered_map<string, int> 
trulyMostPopular(unordered_map<string, int>& names, vector<vector<string> > &synonyms ) {
    unordered_map<string, int> res;
    Graph graph(names);
    graph.connectEdges(synonyms);
    graph.printGraph();
    graph.mergeRecord(res);
    return res;
}

void printMap(const unordered_map<string, int> &names) {
    for (auto it = names.begin(); it != names.end(); it++) {
        cout << it->first << ": "<< it->second << endl;
    }
    cout << endl;
}

int main() {
    unordered_map<string, int> names = {{"John", 10}, {"Jon", 3}, {"Davis", 2}, {"Kari", 3}, {"Johnny", 11}, {"Carlton", 8}, {"Carleton", 2}, {"Jonathan", 9}, {"Carrie", 5}};
    vector<vector<string> > synonyms = {{"Jonathan", "John"}, {"Jon", "Johnny"},{"Johnny", "John"},{"Kari", "Carrie"}, {"Carleton", "Carlton"}};
    printMap(trulyMostPopular(names, synonyms));
    return 0;
}
