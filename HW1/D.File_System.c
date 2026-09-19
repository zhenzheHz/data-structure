#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int id;
    struct Node *next;
} Node;

typedef struct {
    int size;
    Node *head;
    Node *tail;
} Linked_list;

#define MAXN 100005
// Node *pos[MAXN] = {NULL};
Linked_list *file[MAXN] = {NULL};
#undef MAXN

Node* newNode(int x) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->id = x;
    tmp->next = NULL;
    return tmp;
}

Linked_list* newList() {
    Linked_list *list = (Linked_list *) malloc(sizeof(Linked_list));
    list->size = 0;
    list->head = newNode(-1);
    // list->tail = newNode(-1);
    list->tail = list->head;
    list->head->next = NULL;
    return list;
}

bool check_file(int f) {
    if(file[f] == NULL) {
        printf("NOFILE\n");
        return 0;
    }
    return 1;
}

// void insert(Linked_list *list, int index, int x) {
//     Node *tmp = newNode(x), *cur = list->head;
//     for(int i = 0; i < index; i++) {
//         cur = cur->next;
//     }
//     tmp->next = cur->next;
//     cur->next = tmp;
//     list->size++;
// } 

// void push_back(Linked_list *list, int x) {
//     insert(list, list->size, x);
// }

void create(Linked_list *buff, int file_id, int k) {
    if(file[file_id] != NULL) {
        printf("EXIST\n");
        return;
    }
    if(buff->size < k) {
        printf("NOSPACE\n");
        return;
    }
    printf("OK\n");

    file[file_id] = newList();
    if(k == 0) return;

    Node *_head = buff->head->next, *_tail = buff->head;
    for(int i = 0; i < k; i++) {
        _tail = _tail->next;
    }
    buff->head->next = _tail->next;
    file[file_id]->head->next = _head;
    _tail->next = NULL;
    file[file_id]->tail = _tail;
    file[file_id]->size += k;
    buff->size -= k;
    if(buff->size == 0) buff->tail = buff->head;
}

void append(Linked_list *buff, int file_id, int k) {
    if(!check_file(file_id)) return;
    if(buff->size < k) {
        printf("NOSPACE\n");
        return;
    }
    printf("OK\n");
    if(k == 0) return;
    Node *_head = buff->head->next, *_tail = buff->head;
    for(int i = 0; i < k; i++) {
        _tail = _tail->next;
    }
    buff->head->next = _tail->next;
    // Node *last = file[file_id]->tail;
    // last->next = _head;
    // _tail->next = file[file_id]->tail;
    file[file_id]->tail->next = _head;
    _tail->next = NULL;
    file[file_id]->tail = _tail;
    buff->size -= k;
    file[file_id]->size += k;
    if(buff->size == 0) buff->tail = buff->head;
    // printf("OK\n");
}

void truncate(Linked_list *buff, int file_id, int k) {
    if(!check_file(file_id)) return;
    if(file[file_id]->size < k) k = file[file_id]->size;
    printf("OK\n");
    if(k == 0) return;
    Node *bt = buff->tail, *ft = file[file_id]->head;
    for(int i = 0; i < file[file_id]->size-k; i++) {
        ft = ft->next;
    }
    Node *kh = ft->next, *kt = file[file_id]->tail;
    // ft->next = file[file_id]->tail;
    // bt->next = kh;
    // kt->next = buff->tail;
    ft->next = NULL;
    bt->next = kh;
    buff->tail = kt;
    file[file_id]->tail = ft;
    buff->size += k;
    file[file_id]->size -= k;
    // printf("OK\n");
}

void Delete(Linked_list *buff, int file_id) {
    if(!check_file(file_id)) return;
    truncate(buff, file_id, file[file_id]->size);
    free(file[file_id]->head);
    // free(file[file_id]->tail);
    free(file[file_id]);
    file[file_id] = NULL;
    // printf("OK\n");
}

void read(int file_id) {
    if(!check_file(file_id)) return;
    if(file[file_id]->size == 0) {
        printf("EMPTY\n");
        return;
    }
    Node *cur = file[file_id]->head->next;
    for(int i = 0; i < file[file_id]->size; i++, cur = cur->next) {
        printf("%d", cur->id);
        if(i != file[file_id]->size - 1) printf(" ");
        else printf("\n");
    }
}

void frag(int file_id) {
    if(!check_file(file_id)) return;
    if(file[file_id]->size == 0) {
        printf("0\n");
        return;
    }
    int cnt = 0, prev = -10;
    Node *cur = file[file_id]->head->next;
    for(; cur != NULL; prev = cur->id, cur = cur->next) {
        if(prev + 1 != cur->id) {
            cnt++;
        }
    }
    // if(cnt > 0) cnt--;
    printf("%d\n", cnt);
}

int FREE(Linked_list *buff) {
    return buff->size;
}

void release(Linked_list *list) {
    Node *cur = list->head;
    while(cur->next != NULL) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(list);
}

void solve() {
    int N,F,Q;
    scanf("%d%d%d", &N, &F, &Q);

    Linked_list *free_list = newList();

    // for(int i = 0; i < N; i++) {
    //     push_back(free_list, i);
    // }

    Node *last = free_list->head;
    for(int i = 0; i < N; i++) {
        Node *node = newNode(i);
        last->next = node;
        last = node;
    }
    last->next = NULL;
    free_list->tail = last;
    free_list->size = N;

    for(int i = 0; i < Q; i++) {
        char oper[10];
        int f,k;
        scanf("%s", oper);
        if(strcmp(oper, "CREATE") == 0) {
            scanf("%d%d", &f, &k);
            create(free_list, f, k);
        }
        else if(strcmp(oper, "APPEND") == 0) {
            scanf("%d%d", &f, &k);
            append(free_list, f, k);
        }
        else if(strcmp(oper, "TRUNCATE") == 0) {
            scanf("%d%d", &f, &k);
            truncate(free_list, f, k);
        }
        else if(strcmp(oper, "DELETE") == 0) {
            scanf("%d", &f);
            Delete(free_list, f);
        }
        else if(strcmp(oper, "READ") == 0) {
            scanf("%d", &f);
            read(f);
        }
        else if(strcmp(oper, "FRAG") == 0) {
            scanf("%d", &f);
            frag(f);
        }
        else if(strcmp(oper, "FREE") == 0) {
            printf("%d\n", FREE(free_list));
        }
    }
    for(int i = 0; i < F; i++) {
        free(file[i]);
    }
    free(free_list);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    while(T--) solve();
    return 0;
}

