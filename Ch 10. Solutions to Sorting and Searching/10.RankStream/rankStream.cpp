#include <iostream>
#include <vector>
using namespace std;

struct TreeNode{
    int leftNum = 0;
    int val = 0;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
    TreeNode (int v) : val(v) {}
};


class StreamRank {
public:
    StreamRank(){}
    void addNumber(int num) {
        if (root == NULL) {
            root = new TreeNode(num);
            return;
        }
        TreeNode* ptr = root;
        while (ptr) {
            if (ptr->val < num) {
                if (ptr->right == NULL) { 
                    ptr->right = new TreeNode(num);
                    break;
                }
                ptr = ptr->right;
            } else {
                ptr->leftNum++;
                if (ptr->left == NULL){
                    ptr->left = new TreeNode(num);
                    break;
                }
                ptr = ptr->left;
            }
        }
    }

    int getRank(int num) {
        int res = 0;
        if (root == NULL) return -1;
        TreeNode* ptr = root;
        while(ptr) {
            if (ptr->val < num) {
                res += (ptr->leftNum + 1);
                ptr = ptr->right;
            } else if (ptr->val > num) {
                ptr = ptr->left;
            } else {
                res += (ptr->leftNum);
                return res;
            }
        }
        return -1;
    }


    void inorderPrint() {
        print(root);
    }

    ~StreamRank() {
        TreeNode* ptr = root;
        if (ptr == NULL) return;
        deleteNode(ptr);
    }


private:
    TreeNode* root = NULL;
    void deleteNode(TreeNode* ptr) {
        if (ptr->left) 
            deleteNode(ptr->left);
        if (ptr->right)
            deleteNode(ptr->right);
        delete(ptr);
    }

    void print(TreeNode* ptr) {
        if (ptr == NULL) return;
        print(ptr->left);
        cout << "Node: " << ptr->val << "; leftNum: "<< ptr->leftNum << endl;
        print(ptr->right);
   }
};


int main() {
    StreamRank sr;
    vector<int> stream = {5,1,4,4,5,9,7,13,3};
    for (int val : stream) {
        sr.addNumber(val);
    }
    sr.inorderPrint();
    cout << sr.getRank(5) << endl;
    cout << sr.getRank(0) << endl;
    return 0;
}
