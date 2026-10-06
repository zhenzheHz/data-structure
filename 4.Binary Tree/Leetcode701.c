#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode *tmp = malloc(sizeof(struct TreeNode));
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    if(root == NULL) return newNode(val);
    if(val < root->val) root->left = insertIntoBST(root->left, val);
    else root->right = insertIntoBST(root->right, val);
    return root;
}