// Author : e24154752
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 4096
#define MAX_SIZE 1024

typedef struct {
    char school[MAX_SIZE];
    char department[MAX_SIZE];
    char day[MAX_SIZE];
    char edu[MAX_SIZE];
    int num_of_student;
    int num_of_teacher;
    int num_of_graduate;
} Data;

typedef struct _Node {
    Data data;
    struct _Node *left;
    struct _Node *right;
} Node;

static void __print_data(int *cnt, const Data data) {
    printf("[%d]\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n", 
        *cnt, 
        data.school, 
        data.department, 
        data.day, 
        data.edu, 
        data.num_of_student,
        data.num_of_teacher, 
        data.num_of_graduate
    );
}

static void strip_the_number(char *str) {
    char *tmp = str;
    for(char *ch = str; *ch; ch++) {
        if(*ch != ',' && *ch != '"') {
            *tmp++ = *ch;
        }
    }
    *tmp = '\0';
}

// void split_the_data(char *line, Data *res) {
//     char *split[20];
//     int index = 0;

//     split[index++] = line;

//     for(int i = 0; line[i] != '\0'; i++) {
//         if(line[i] == '\t' || line[i] == '\n' || line[i] == '\r') {
            
//             line[i] = '\0';
        
//             if(index < 20 && line[i+1] != '\0' && line[i+1] != '\n' && line[i+1] != '\r') {
//                 split[index++] = &line[i+1];
//             }
//         }
//     }

//     strcpy(res->school, split[1]);
//     strcpy(res->department, split[3]);
//     strcpy(res->day, split[4]);
//     strcpy(res->edu, split[5]);
//     strip_the_number(split[6]);
//     strip_the_number(split[7]);
//     strip_the_number(split[8]);
//     res->num_of_student = atoi(split[6]);
//     res->num_of_teacher = atoi(split[7]);
//     res->num_of_graduate = atoi(split[8]);
// }

void split_the_data(char *line, Data *res) {
    char *split[12];
    int index = 0;
    
    split[index++] = line;
    for(int i = 0; line[i] != '\0'; i++) {
        if(line[i] == '\t') {
            line[i] = '\0';
            if (index < 12) {
                split[index++] = &line[i+1];
            }
        }
    }

    strcpy(res->school, split[1]);
    strcpy(res->department, split[3]);
    strcpy(res->day, split[4]);
    strcpy(res->edu, split[5]);
    
    strip_the_number(split[6]);
    strip_the_number(split[7]);
    strip_the_number(split[8]);
    
    res->num_of_student = atoi(split[6]);
    res->num_of_teacher = atoi(split[7]);
    res->num_of_graduate = atoi(split[8]);
}

Node* newNode(const Data _data) {
    Node *tmp = malloc(sizeof(Node));
    tmp->data = _data;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

Node* insert(Node *root, Data key) {
    if(root == NULL) return newNode(key);

    if(strcmp(key.school, root->data.school) < 0) {
        root->left = insert(root->left, key);
    }
    else {
        root->right = insert(root->right, key);
    }
    return root;
}

Node* _remove_succ(Node* root, Node** succ_out) {
    if (root->left == NULL) {
        *succ_out = root;
        return root->right;
    }
    root->left = _remove_succ(root->left, succ_out);
    return root;
}

Node* erase(Node *root, const char *_school, int *count) {
    if(root == NULL) return NULL;

    int cmp = strcmp(_school, root->data.school);

    if(cmp < 0) {
        root->left = erase(root->left, _school, count);
        return root;
    }
    else if(cmp > 0) {
        root->right = erase(root->right, _school, count);
        return root;
    }
    else {
        (*count)++;
        __print_data(count, root->data);

        if(root->left == NULL) {
            Node *tmp = root->right;
            free(root);
            return erase(tmp, _school, count);
        }

        if(root->right == NULL) {
            Node *tmp = root->left;
            free(root);
            return tmp;
        }

        Node* succ_node = NULL;
        root->right = _remove_succ(root->right, &succ_node);
        root->data = succ_node->data;
        free(succ_node);
        return erase(root, _school, count);
        // root->right = erase(root->right, _school, count);
        // if (strcmp(_school, root->data.school) == 0) {
        //     return erase(root, _school, count);
        // }

        // return root;
    }
}

void search(Node *root, char *_school, int *count) {
    if(root == NULL) return;
    int cmp = strcmp(_school, root->data.school);
    if(cmp < 0) search(root->left, _school, count);
    else if(cmp > 0) search(root->right, _school, count);
    else {
        (*count)++;
        __print_data(count, root->data);
        search(root->right, _school, count);
    }
}

int get_height(Node *root) {
    if(root == NULL) return 0;
    int lh = get_height(root->left);
    int rh = get_height(root->right);
    return (lh > rh? lh : rh) + 1;
}

int main() {

    Node *root = NULL;

    char line[LINE_SIZE];
    int mode = -1;
    while(fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[--len] = '\0';
        }
        
        int new_mode;

        if (len == 1 && line[0] >= '0' && line[0] <= '3') {
            new_mode = line[0] - '0';
            if(mode == 1) {
                printf("Tree height = %d\n", get_height(root));
            }
            if(new_mode == 0) break;
            mode = new_mode;
            continue;
        }

        // printf("mode : %d\n", mode);
        // printf("check : %s\n", line);

        if(mode == 1) {
            Data new_data;
            split_the_data(line, &new_data);
            // __print_data(new_data);
            root = insert(root, new_data);
        }

        if(mode == 2) {
            if (root == NULL) {
                printf("Tree is empty!\n");
                continue;
            }
            printf("Search results:\n");
            int search_count = 0;
            search(root, line, &search_count);
            if (search_count == 0) printf("There is no match!\n");
        }

        if(mode == 3) {
            if (root == NULL) {
                printf("Tree is empty!\n");
                continue;
            }
            printf("Delete records:\n");
            int del_count = 0;
            root = erase(root, line, &del_count);
            if (del_count == 0) printf("There is no match!\n");
            printf("Tree height = %d\n", get_height(root));
        }

    }
    return 0;
}
