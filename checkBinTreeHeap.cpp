// C Program to Check if a given
// Binary Tree is a Heap

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to count the number of nodes in the binary tree
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to check if the binary tree is complete or not
int isCompleteUtil(struct Node* root, int index, int numberOfNodes) {
    if (root == NULL)
        return 1;

    // If index assigned to current node is more than 
    // number of nodes in the tree, then the tree is not complete
    if (index >= numberOfNodes)
        return 0;

    // Recur for left and right subtrees
    return isCompleteUtil(root->left, 2 * index + 1, numberOfNodes) &&
           isCompleteUtil(root->right, 2 * index + 2, numberOfNodes);
}

// Function to check the heap property in the tree
int isHeapUtil(struct Node* root) {
  
    // If the node is a leaf
    if (root->left == NULL && root->right == NULL)
        return 1;

    // If there is no right child, check heap property for left child
    if (root->right == NULL) {
        return root->key >= root->left->key;
    } else {
      
        // Check heap property at the node and recursively check
        // the heap property at left and right subtrees
        if (root->key >= root->left->key && root->key >= root->right->key)
            return isHeapUtil(root->left) && isHeapUtil(root->right);
        else
            return 0;
    }
}

// Function to check if the binary tree is a heap or not
int isHeap(struct Node* root) {
    int nodeCount = countNodes(root);
    int index = 0;

    if (isCompleteUtil(root, index, nodeCount) && isHeapUtil(root))
        return 1;
    return 0;
}

struct Node* createNode(int key) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
  
    // Construct the Binary Tree
    //        10
    //       /  \
    //      9    8
    //     / \   / \
    //    7   6 5   4

    struct Node* root = createNode(10);
    root->left = createNode(9);
    root->right = createNode(8);
    root->left->left = createNode(7);
    root->left->right = createNode(6);
    root->right->left = createNode(5);
    root->right->right = createNode(4);

    if (isHeap(root)) {
       printf("true");
    } else printf("false");

    return 0;
}

