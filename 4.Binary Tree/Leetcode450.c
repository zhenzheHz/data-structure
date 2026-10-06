#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *find_min(struct TreeNode *root) {
    struct TreeNode *cur = root;
    while(cur && cur->left) {
        cur = cur->left;
    }
    return cur;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if(root == NULL) return NULL;
    
    if(key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if(root->left == NULL) {
            struct TreeNode *tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL) {
            struct TreeNode *tmp = root->left;
            free(root);
            return tmp;
        }
        
        struct TreeNode *tmp = find_min(root->right);
        root->val = tmp->val;
        root->right = deleteNode(root->right, tmp->val);
    }
    return root;
}