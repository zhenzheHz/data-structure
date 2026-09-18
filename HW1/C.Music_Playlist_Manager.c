#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int id;
    char song[25];
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    int size;
    Node *head;
    Node *tail;
    Node *cur;
} Linked_list;

#define MAXN 400005
Node* pos[MAXN] = {NULL};

Node* newNode(const char _song[], int _id);
Linked_list* newList();

bool empty(Linked_list *list);
// void push_back(Linked_list *list, const char _song[], int _id);
void insert_next(Linked_list *list, const char _song[], int _id, Node* tar);
void erase(Linked_list *list, int _id);
void print(Linked_list *list);
void print_now(Linked_list *list);
void release(Linked_list *list);

void solve() {
    int n,Q;
    char oper[10], x[25];
    scanf("%d%d", &n, &Q);
    Linked_list *music = newList();

    for(int i = 0; i < n; i++) {
        scanf("%s", x);
        insert_next(music, x, i+1, music->tail->prev);
    }

    music->cur = music->head->next;
    int new_id = n+1, k;

    while(Q--) {
        scanf("%s", oper);
        if(strcmp(oper, "ADD") == 0) {
            scanf("%s", x);
            bool wasEmpty = empty(music);
            insert_next(music, x, new_id++, music->tail->prev);
            if(wasEmpty) music->cur = music->tail->prev;
        }
        else if(strcmp(oper, "INSERT") == 0) {
            scanf("%s", x);
            bool wasEmpty = empty(music); 
            insert_next(music, x, new_id++, music->cur);
            if(wasEmpty) music->cur = music->tail->prev;
        }
        else if(strcmp(oper, "DEL") == 0) {
            scanf("%d", &k);
            erase(music, k);
        }
        else if(strcmp(oper, "NEXT") == 0) {
            if(music->cur->next != music->tail) {
                music->cur = music->cur->next;
            }
        }
        else if(strcmp(oper, "PREV") == 0) {
            if(music->cur->prev != music->head) {
                music->cur = music->cur->prev;
            }
        }
        else if(strcmp(oper, "PRINT") == 0) {
            print(music);
        }
        else if(strcmp(oper, "NOW") == 0) {
            print_now(music);
        }
    }
    release(music);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    while(T--) solve();
    return 0;
}

Node* newNode(const char _song[], int _id) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->id = _id;
    strcpy(tmp->song, _song);
    tmp->next = NULL;
    tmp->prev = NULL;
    pos[_id] = tmp;
    return tmp;
}

Linked_list* newList() {
    Linked_list *tmp = (Linked_list*) malloc(sizeof(Linked_list));
    tmp->size = 0;
    tmp->head = newNode("", MAXN-1);
    tmp->tail = newNode("", MAXN-2);
    tmp->head->next = tmp->tail;
    tmp->tail->prev = tmp->head;
    tmp->head->prev = tmp->head;
    tmp->tail->next = NULL;
    tmp->cur = tmp->head;
    return tmp;
}

bool empty(Linked_list *list) {
    return list->size == 0;
}

void insert_next(Linked_list *list, const char _song[], int _id, Node* tar) {
    Node *tmp = newNode(_song, _id);
    tmp->next = tar->next;
    tmp->prev = tar;
    tar->next->prev = tmp;
    tar->next = tmp;
    list->size++;
}

void erase(Linked_list *list, int _id) {
    if(pos[_id] == NULL) return;
    Node *song = pos[_id];
    if(song == list->cur) {
        if(song->next == list->tail) {
            list->cur = list->cur->prev;
        }
        else {
            list->cur = list->cur->next;
        }
    }
    song->prev->next = song->next;
    song->next->prev = song->prev;
    free(song);
    pos[_id] = NULL;
    list->size--;
}

void print(Linked_list *list) {
    if(empty(list)) { printf("EMPTY\n");return; }
    Node *now = list->head->next;
    while(now != list->tail) {
        printf("%s%c", now->song, (now->next == list->tail) ? '\n' : ' ');
        now = now->next;
    }
    // printf("\n");
}

void print_now(Linked_list *list) {
    if(empty(list)) printf("EMPTY\n");
    else printf("%s\n", list->cur->song);
}

void release(Linked_list *list) {
    if(list != NULL) {
        Node *tmp = list->head;
        while(tmp->next != NULL) {
            Node *nxt = tmp->next;
            free(tmp);
            tmp = nxt;
        }
        free(list);
    }
}