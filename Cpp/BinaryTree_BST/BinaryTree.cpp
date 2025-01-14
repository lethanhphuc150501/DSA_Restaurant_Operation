#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;  // Cho phép lớp Binary Tree truy cập vào vùng private của lớp Node
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN 
    int tree_height(Node* root) {
        if (root == NULL) return 0;
        Node* tmp = root;
        int left = tree_height(root->pLeft);
        int right = tree_height(root->pRight);
        if (left > right) return 1 + left;
        else return 1 + right;
    }

    int getHeight() {
        // TODO: return height of the binary tree.
        return tree_height(root);
    }

    void printPreorder(Node* node) {
        if (node == NULL) return;
        cout << node->value << " ";
        printPreorder(node->pLeft);
        printPreorder(node->pRight);
    }

    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        printPreorder(root);
        return "";
    }

    void printInorder(Node* node) {
        if (node == NULL) return;
        printInorder(node->pLeft);
        cout << node->value << " ";
        printPostorder(node->pRight);
    }

    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        printInorder(root);
        return "";
    }

    void printPostorder(Node* node) {
        if (node == NULL) return;
        printPostorder(node->pLeft);
        printPostorder(node->pRight);
        cout << node->value << " ";
    }

    string postOrder() {
        printPostorder(root);
        return "";
    }

    int countTwoChildrenInSubTree(Node* node) {
        if (node == NULL) return 0;
        int left = countTwoChildrenInSubTree(node->pLeft);
        int right = countTwoChildrenInSubTree(node->pRight);
        if (node->pLeft != NULL && node->pRight != NULL) return 1 + left + right;
        else return left + right;
    }

    int countTwoChildrenNode() {
        return countTwoChildrenInSubTree(root);
    }

    V calculateSumOfLeafs(Node* node) {
        if (node == NULL) return 0;
        int sum_left = calculateSumOfLeafs(node->pLeft);
        int sum_right = calculateSumOfLeafs(node->pRight);
        if (node->pLeft == NULL && node->pRight == NULL) return node->value + sum_left + sum_right;
        else return sum_left + sum_right;
    }

    V sumOfLeafs() {
        return calculateSumOfLeafs(root);
    }

    void printLevel(int level, Node* node) {
        if (node == NULL) return;
        if (level == 1) cout << node->value << " ";
        if (level > 1) {
            printLevel(level - 1, node->pLeft);
            printLevel(level - 1, node->pRight);
        }
    }

    void BFS() {
        for (int i = 1; i <= this->getHeight(); i++) {
            printLevel(i, root);
        }
    };

    bool isBST(Node *node) {
        if (node == NULL) return true;
        bool left = isBST(node->pLeft);
        bool right = isBST(node->pRight);
        bool current = true;
        if (node->pLeft != NULL) {
            if (node->value > node->pLeft->value) current = true;
            else return false;
        }
        if (node->pRight != NULL) {
            if (node->value < node->pRight->value) current = true;
            else return false;
        }
        return current & left & right;
    }

    bool isBST() {
        return isBST(root);
    }

    int getDiameter() {
        return 1 + tree_height(root->pLeft) + tree_height(root->pRight);
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",1, 4);
    binaryTree.addNode("L",2, 6);
    binaryTree.addNode("R",3, 9);
    binaryTree.addNode("LL",4, 10);
    cout << binaryTree.getDiameter();
    return 0;
}