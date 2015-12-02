#include <iostream>
#include <vector>

using namespace std;

class BiNode {
public:
    int val;
    BiNode *node1 = NULL;
    BiNode *node2 = NULL;
    BiNode(){}
    BiNode(int v): val(v){}
};

class NodePair {
public:
    BiNode *head = NULL, *tail = NULL;
    NodePair(BiNode *node1, BiNode *node2): head(node1), tail(node2) {}
};

void concat(BiNode* n1, BiNode *n2) {
    n1->node2 = n2;
    n2->node1 = n1;
}

NodePair convert(BiNode* root) {
    if (root == NULL) return NodePair(NULL, NULL);
    
    NodePair part1 = convert(root->node1);
    NodePair part2 = convert(root->node2);

    if (part1.head) {
        concat(part1.tail, root);
    }
    if (part2.head) {
        concat(root, part2.head);
    }

    return NodePair(part1.head ? part1.head : root, part2.head ? part2.tail : root);
}

ostream &operator<<(ostream &os, const NodePair &np) {
    //  BiNode *head = np->head;
    BiNode *tail = np.tail;
    BiNode *ptr = np.head;
    while(ptr != tail) {
        os << ptr->val<< " ";
        ptr = ptr->node2;
    }
    if (tail) 
        os << tail->val;
    return os;
}

int main() {
    BiNode node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
    
    node1.node1 = &node0;
    node2.node1 = &node1;
    node2.node2 = &node3;
    node4.node1 = &node2;
    node4.node2 = &node5;
    node5.node2 = &node6;

    cout << convert(&node4) << endl;

    return 0;
}
