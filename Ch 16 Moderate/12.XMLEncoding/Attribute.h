#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

class Attribute {
public:
    std::string tag;
    std::string value;
    Attribute(const std::string &t, const std::string &v) {
        tag = t;
        value = v;
    }
    
    std::string getTagCode() {
        if (tag == "family") {
            return "1";
        } else if (tag == "person") {
            return "2";
        } else if (tag == "firstName") {
            return "3";
        } else if (tag == "lastName") {
            return "4";
        } else if (tag == "state") {
            return "5";
        }
        return "--";
    }
};

#endif
