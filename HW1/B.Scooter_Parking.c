#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* newQueue();
bool empty(Queue *q);
void check(Queue *q);
void push(Queue *q, double x);
void pop(Queue *q);
double front(Queue *q);
void release(Queue *q);

void solve() {
    int n,m;
    scanf("%d%d", &n, &m);
    Queue *q1 = newQueue(), *q2 = newQueue();
    double cur = -1.0, prev = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lf", &cur);
        if(i != 0) {
            push(q1, cur - prev);
            // printf("%.6f\n", cur - prev);
        }
        prev = cur;
    }
    for(int i = 0; i < m; i++) {
        double ans;
        if (!empty(q1) && !empty(q2)) {
            if (front(q1) >= front(q2)) {
                ans = front(q1);
                pop(q1);
            } else {
                ans = front(q2);
                pop(q2);
            }
        } else if (!empty(q1)) {
            ans = front(q1);
            pop(q1);
        } else {
            ans = front(q2);
            pop(q2);
        }
        // printf("db : %.6f\n", ans);
        printf("%.6f\n", ans/2.0);
        push(q2, ans/2.0);
        push(q2, ans/2.0);
    }
    release(q1);
    release(q2);
}

int main() {
    solve();
    return 0;
}

Queue* newQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->data = malloc(sizeof(double));
    q->capacity = 1;
    q->front = q->capacity - 1;
    q->rear = q->capacity - 1;
    q->size = 0;
    return q;
}

bool empty(Queue *q) {
    return q->size == 0;
}

void check(Queue *q) {
    if(q->size == q->capacity - 1) {
        double *tmp = malloc(2*q->capacity*sizeof(double));
        for(int i = 0; i < q->size; i++) {
            int idx = (q->front + i + 1) % q->capacity;
            tmp[i] = q->data[idx];
        }
        free(q->data);
        if(tmp != NULL) q->data = tmp;
        q->capacity *= 2;
        q->front = q->capacity - 1;
        q->rear = q->size - 1;
    }
}

void push(Queue *q, double x) {
    check(q);
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = x;
    q->size++;
}

void pop(Queue *q) {
    if(empty(q)) return;
    q->front = (q->front + 1) % q->capacity;
    q->size--;
}

double front(Queue *q) {
    if(empty(q)) return -1.0;
    int idx = (q->front + 1) % q->capacity;
    return q->data[idx];
}

void release(Queue *q) {
    if(q != NULL) {
        if(q->data != NULL) {
            free(q->data);
        }
        free(q);
    }
}