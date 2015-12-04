#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

using DocPair=pair<int, int>;

class Document{
public:
    vector<int> words;
    int docId;
    Document(int id, vector<int> w): docId(id), words(w) {}
};

class pairHash {
public:
    template <typename T1, typename T2> 
    size_t operator() (const pair<T1, T2> &x) const {
        return hash<T1>()(x.first) ^ hash<T2>()(x.second);
    }
};

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    for (const T &v : vec) {
        os << " " << v;
    }
    return os;
}

ostream &operator<<(ostream &os, const Document &doc) {
    os << doc.docId << ": {" << doc.words << "}" << endl;
    return os;
}

ostream &operator<<(ostream &os, const unordered_map<int, list<int> > &groups) {
    for (auto it = groups.begin(); it != groups.end(); it++) {
        os << it->first << "-> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return os;
}

unordered_map<int, list<int> > 
groupWords(const vector<Document> &doc) {
    unordered_map<int, list<int> > res;
    for (size_t i = 0; i < doc.size(); i++) {
        for (size_t j = 0; j < doc[i].words.size(); j++) {
            res[doc[i].words[j]].push_back(doc[i].docId);
        }
    }
    return res;
}


ostream &operator<<(ostream &os, const unordered_map<DocPair, double, pairHash> &similarity)
{
    os << "ID1\tID2\tSimilarity" << endl;
    for (auto it = similarity.begin(); it != similarity.end(); it++) {
        os << it->first.first << '\t' << it->first.second << '\t' << it->second << endl;
    }
    return os;
}

void calculateSimilarity(const vector<Document> &docs, unordered_map<DocPair, double, pairHash> &res) {
    unordered_map<int, int> id2Idx;
    for (int i = 0; i < docs.size(); i++) {
        id2Idx[docs[i].docId] = i;
    }
    for (auto it = res.begin(); it != res.end(); it++){
        int size1 = docs[id2Idx[it->first.first]].words.size();
        int size2 = docs[id2Idx[it->first.second]].words.size();
        it->second = it->second / static_cast<double>(size1 - it->second + size2);
    }
}

unordered_map<DocPair, double, pairHash>
computeSimilarities(vector<Document> &docs) {
    auto wordGroups = groupWords(docs);
    unordered_map<DocPair, double, pairHash> res;
    for (auto it = wordGroups.begin(); it != wordGroups.end(); it++) {
        for (auto listIt = it->second.begin(); listIt != it->second.end(); listIt++) {
            auto listIt2 = listIt;
            listIt2++;
            for (; listIt2 != it->second.end(); listIt2++) {
                DocPair cur = make_pair(*listIt, *listIt2);
                //if (res.count(cur)) 
                res[cur] += 1.0;
            }
        }
    }
    
    calculateSimilarity(docs, res);
    return res;
}

int main() {
    vector<Document> docs = {Document(12, {1,5,9}), Document(13, {5,3,1,8}), Document(14, {4,3,2}), Document(15, {1,5,9,8}), Document(17, {1,6})};
    cout << docs << endl;
    //    auto wordGroups = groupWords(docs);
    cout << computeSimilarities(docs) << endl;
    return 0;
}
