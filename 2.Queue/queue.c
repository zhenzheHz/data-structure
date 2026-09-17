#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int *data;
    int capacity;
    int size;
    int front;
    int rear;
};

void createQ(struct Queue *que) {
    que->data = malloc(sizeof(int));
    que->capacity = 1;
    que->size = 0;
    que->front = que->capacity - 1;
    que->rear = que->capacity - 1;
}

bool IsFullQ(struct Queue *que) {
    return que->size == que->capacity;
}

bool IsEmpty(struct Queue *que) {
    return que->size == 0;
}

void QueueFull(struct Queue *que) {
    if(!IsFullQ(que)) return;
    int new_capacity = que->capacity * 2;
    int *tmp = malloc(new_capacity * sizeof(int));
    for(int i = 0; i < que->size; i++) {
        int index = (que->front + 1 + i) % que->capacity;
        tmp[i] = que->data[index];
    }
    free(que->data);
    que->data = tmp;
    que->capacity = new_capacity;
    que->front = que->capacity - 1;
    que->rear = que->size - 1;
}

void AddQ(struct Queue *que, int val) {
    if(IsFullQ(que)) QueueFull(que);
    que->rear = (que->rear + 1) % que->capacity;
    que->data[que->rear] = val; 
    que->size++;
}

int DeleteQ(struct Queue *que) {
    if(IsEmpty(que)) return -1;
    que->front = (que->front + 1) % que->capacity;
    que->size--;
    return que->data[que->front];
}

int main() {
    return 0;
}