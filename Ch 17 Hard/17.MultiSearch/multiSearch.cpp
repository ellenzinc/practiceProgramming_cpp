#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

ostream &operator<<(ostream &os, const unordered_map<string, int> &v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << it->first << ": "<< it->second << endl;
    }
    return os;
}

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isWord = false;
    TrieNode(){};
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    void addTrie(string &word) {
        TrieNode* ptr = root;
        for (char c : word) {
            if ((ptr->children).count(c) == 0) {
                ptr->children[c] = new TrieNode();
            }
            ptr = ptr->children[c];
        }
        ptr->isWord = true;
    }
    
    vector<string> searchWord(string &word, int start) {
        TrieNode* ptr = root;
        vector<string> res;
        string cur;
        for (int i = start; i < word.size(); i++) {
            if ((ptr->children).count(word[i]) == 0)
                return res;
            else {
                cur += word[i];
                ptr = ptr->children[word[i]];
                if (ptr->isWord)
                    res.push_back(cur);
            }
        }
        return res;
    }
    
    void printTrie() const {
        const TrieNode* ptr = root;
        queue<const TrieNode*> q;
        q.push(ptr);
        while(!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto it = cur->children.cbegin(); it != cur->children.cend(); it++) {
                cout << it->first << " ";
                q.push(it->second);
            }
            cout << endl;
        }
    }

private:
    TrieNode* root = NULL;
};

unordered_map<string, int>
searchAll(string &big, vector<string> &vec) {
    unordered_map<string, int> res;
    Trie trie;
    for (int i = 0; i < vec.size(); i++) {
        trie.addTrie(vec[i]);
    }

    // trie.printTrie();
    // cout << endl;
    for (int i = 0; i < big.size(); i++) {
        vector<string> tmp = trie.searchWord(big, i);
        if (!tmp.empty()) {
            for (int j = 0; j < tmp.size(); j++) 
                res[tmp[j]] = i;
        }
    }
    return res;
}

int main() {
    string big = "mississippi";
    vector<string> vec = {"is", "ppi", "hi", "sis", "i", "ssippi"};
    cout << searchAll(big, vec) << endl;
}
