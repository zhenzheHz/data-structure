// Problem : https://zerojudge.tw/ShowProblem?problemid=e447
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
    int front;
    int rear;
} Queue;

void init(Queue *que) {
    que->data = malloc(sizeof(int));
    que->size = 0;
    que->capacity = 1;
    que->front = que->capacity - 1;
    que->rear = que->capacity - 1;
}

bool Full(Queue *que) {
    return que->size == que->capacity;
}

bool Empty(Queue *que) {
    return que->size == 0;
}

void CheckFull(Queue *que) {
    if(!Full(que)) return;
    int *tmp = malloc(que->capacity * 2 * sizeof(int));
    for(int i = 0; i < que->size; i++) {
        int index = (que->front + 1 + i) % que->capacity;
        tmp[i] = que->data[index];
    }
    free(que->data);
    if(tmp != NULL) que->data = tmp;
    que->capacity *= 2;
    que->front = que->capacity - 1;
    que->rear = que->size - 1;
}

void Push(Queue *que, int val) {
    CheckFull(que);
    que->rear = (que->rear + 1) % que->capacity;
    que->size++;
    que->data[que->rear] = val;
}

int Front(Queue *que) {
    if(Empty(que)) return -1;
    int index = (que->front + 1) % que->capacity;
    return que->data[index];
}

void Pop(Queue *que) {
    if(Empty(que)) return;
    que->front = (que->front + 1) % que->capacity;
    que->size--;
}

void Release(Queue *que) {
    if(que->data != NULL) {
        free(que->data);
        que->data = NULL;
    }
}

int main() {
    int N,k,x;
    scanf("%d", &N);
    Queue q;
    init(&q);
    while(N--) {
        scanf("%d", &k);
        if(k == 1) {
            scanf("%d", &x);
            Push(&q, x);
        }
        else if(k == 2) {
            printf("%d\n", Front(&q));
        }
        else {
            Pop(&q);
        }
    }
    Release(&q);
    return 0;
}