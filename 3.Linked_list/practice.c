// Problem : https://oj.ntucpc.org/problems/667
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Linked_list;

// const int MAXN = 1e5+5;

#define MAXN 100005

Node* pos[MAXN] = {NULL};

Node* newNode(int val);
Linked_list* newLinkedList();
void insert_prev(Linked_list *list, int tar, int x);
void insert_next(Linked_list *list, int tar, int x);
void print_prev(Linked_list *list, int x);
void print_next(Linked_list *list, int x);
void erase(Linked_list *list, int x);
void release(Linked_list *list);
void push_front(Linked_list *list, int x);
void push_back(Linked_list *list, int x);

void solve() {
    int m,operation,x,tar;
    scanf("%d", &m);
    Linked_list *lst = newLinkedList();
    for(int i = 0; i < m; i++) {
        scanf("%d", &operation);
        switch(operation) {
            case 1:
                scanf("%d", &x);
                push_front(lst, x);
                break;
            case 2:
                scanf("%d", &x);
                push_back(lst, x);
                break;
            case 3:
                scanf("%d%d", &x, &tar);
                insert_prev(lst, tar, x);
                break;
            case 4:
                scanf("%d%d", &x, &tar);
                insert_next(lst, tar, x);
                break;
            case 5:
                scanf("%d", &x);
                print_prev(lst, x);
                break;
            case 6:
                scanf("%d", &x);
                print_next(lst, x);
                break;
            case 7:
                scanf("%d", &x);
                erase(lst, x);
                break;
        }
    }
    release(lst);
}

int main() {
    solve();
    return 0;
}


Node* newNode(int val) {
    Node *ret = (Node*)malloc(sizeof(Node));
    ret->next = NULL;
    ret->prev = NULL;
    ret->val = val;
    pos[val] = ret;
    return ret;
}

Linked_list* newLinkedList(){
    Linked_list *list = (Linked_list*)malloc(sizeof(Linked_list));
    list->size = 0;
    list->head = newNode(MAXN-1);
    list->tail = newNode(MAXN-1);
    list->head->next = list->tail;
    list->tail->prev = list->head;
    return list;
}

void push_front(Linked_list *list, int x) {
    Node *tmp = newNode(x);
    tmp->next = list->head->next;
    list->head->next->prev = tmp;
    list->head->next = tmp;
    tmp->prev = list->head;
    list->size++;
}

void push_back(Linked_list *list, int x) {
    Node *tmp = newNode(x);
    tmp->prev = list->tail->prev;
    tmp->next = list->tail;
    list->tail->prev->next = tmp;
    list->tail->prev = tmp;
    list->size++;
}

void insert_prev(Linked_list *list, int tar, int x) {
    if(pos[tar] == NULL) {
        printf("peko\n");
        return;
    }
    Node *cur = pos[tar], *tmp = newNode(x);
    tmp->next = cur;
    tmp->prev = cur->prev;
    cur->prev->next = tmp;
    cur->prev = tmp;
    list->size++;
}

void insert_next(Linked_list *list, int tar, int x) {
    if(pos[tar] == NULL) {
        printf("peko\n");
        return;
    }
    Node *cur = pos[tar], *tmp = newNode(x);
    tmp->next = cur->next;
    tmp->prev = cur;
    cur->next->prev = tmp;
    cur->next = tmp;
    list->size++;
}

void print_prev(Linked_list *list, int x) {
    if(pos[x] == NULL) {
        printf("peko\n");
    }
    else if(pos[x]->prev == list->head) {
        printf("NULL\n");
    }
    else {
        printf("%d\n", pos[x]->prev->val);
    }
}

void print_next(Linked_list *list, int x) {
    if(pos[x] == NULL) {
        printf("peko\n");
    }
    else if(pos[x]->next == list->tail) {
        printf("NULL\n");
    }
    else {
        printf("%d\n", pos[x]->next->val);
    }
}

void erase(Linked_list *list, int x) {
    if(pos[x] == NULL) {
        printf("peko\n");
        return;
    }
    Node *tmp = pos[x];
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    pos[x] = NULL;
    free(tmp);
    list->size--;
}

void release(Linked_list *list) {
    if(list == NULL) return;
    Node *cur = list->head;
    while(cur != NULL) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(list);
}