#include <iostream>
#include <vector>

using namespace std;

class BiNode {
public:
    int val;
    BiNode *left = NULL;
    BiNode *right = NULL;
    
    BiNode(int v): val(v){}
};

void concat(BiNode* n1, BiNode *n2) {
    n1->right = n2;
    n2->left = n1;
}

BiNode *convertToCircular(BiNode *root) {
    if (root == NULL) return NULL;
    BiNode *part1 = convertToCircular(root->left);
    BiNode *part3 = convertToCircular(root->right);
    
    if (part1 == NULL && part3 == NULL) {
        root->left = root;
        root->right = root;
        return root;
    }

    BiNode* tail3 = part3 == NULL ? NULL : part3->left;
    
    // join left to root;
    if (part1)
        concat(part1->left, root);
    else 
        concat(part3->left, root);

    // join root to right
    if (part3) 
        concat(root, part3);
    else
        concat(root, part1);

    // join right to left;
    if (part1 && part3) {
        concat(tail3, part1);
    }

    return part1 == NULL ? root : part1;
}

BiNode* convert(BiNode *root) {
    BiNode *head = convertToCircular(root);
    head->left->right = NULL;
    head->left = NULL;
    return head;
}

ostream & operator<<(ostream &os, const BiNode* root) {
    while(root) {
        os << root->val << " ";
        root = root->right;
    }
    return os;
}

int main() {
    BiNode node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
    
    node1.left = &node0;
    node2.left = &node1;
    node2.right = &node3;
    node4.left = &node2;
    node4.right = &node5;
    node5.right = &node6;
    
    cout << convert(&node4) << endl;
    
    return 0;
}
