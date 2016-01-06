#include "Element.h"

using namespace std;

void encode(string v, string &res) {
    res += v;
    res += " ";
}

void encode(Attribute &attr, string &res) {
    encode(attr.getTagCoe(), res);
    encode(attr.value, res);
} 

void encode(Element &root, string &res) {
    
}

string encodeToString(Element &root) {
    string res;
    encode(root, res);
    return res;
}

int main() {
    Element root("family");
    //    Attribute a1("lastName", "mcdowell");
    //    Attribute a2("state", "CA");
    root.insert(Attribute("lastName", "mcdowell"));
    root.insert(Attribute("state", "CA"));
    
    Element child("person", "Some Message");
    child.insert(Attribute("firstName", "Gayle"));
    
    root.insert(&child);
    return 0;
}
