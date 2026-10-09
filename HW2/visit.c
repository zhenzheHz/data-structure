#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n, *preorder, *postorder, *inorder;

bool is_unique = 1;

int id = 0;

void dfs(int pre_L, int pre_R, int post_L, int post_R) {
    if(pre_L > pre_R) return;
    if(pre_L == pre_R) {
        inorder[id++] = preorder[pre_L];
        return;
    }
    int root = preorder[pre_L];
    int left = preorder[pre_L+1], right = postorder[post_R-1];
    if(left == right) {
        is_unique = 0;
        dfs(pre_L+1, pre_R, post_L, post_R-1);
        inorder[id++] = root;
    }
    else {
        int idx = -1;
        for(int i = post_L; i <= post_R; i++) {
            if(postorder[i] == left) {
                idx = i;
                break;
            }
        }
        int size_of_left_tree = idx - post_L + 1;
        dfs(pre_L + 1, pre_L + size_of_left_tree, post_L, idx);
        inorder[id++] = root;
        dfs(pre_L + size_of_left_tree + 1, pre_R, idx + 1, post_R - 1);
    }
}

int main() {
    scanf("%d", &n);
    preorder = malloc(n * sizeof(int));
    postorder = malloc(n * sizeof(int));
    inorder = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }
    dfs(0, n-1, 0, n-1);

    for(int i = 0; i < n; i++) {
        printf("%d ", inorder[i]);
    }
    printf("\n");
    
    if (is_unique) {
        printf("UNIQUE\n");
    } else {
        printf("NOT UNIQUE\n");
    }

    return 0;
}
