#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *data;
    int capacity;
    int top;
} Stack;

char str[1005];

Stack* newStack();
void push(Stack *stk, int x);
void pop(Stack *stk);
int top(Stack *stk);
bool empty(Stack *stk);
void check(Stack *stk);
void release(Stack *stk);


void solve() {
    scanf("%s", str);
    int match = 0, len = strlen(str);
    Stack *stk = newStack();
    bool valid = 1;
    for(int i = 0; i < len; i++) {
        switch(str[i]) {
            case '(':
                push(stk, 1);
                break;
            case '[':
                push(stk, 2);
                break;
            case '{':
                push(stk, 3);
                break;
            case ')':
                if(empty(stk) || top(stk) != 1) valid = 0;
                else {
                    match++;
                    pop(stk);
                }
                break;
            case ']':
                if(empty(stk) || top(stk) != 2) valid = 0;
                else {
                    match++;
                    pop(stk);
                }
                break;
            case '}':
                if(empty(stk) || top(stk) != 3) valid = 0;
                else {
                    match++;
                    pop(stk);
                }
                break;
        }
        if(!valid) break;
    }
    if(!empty(stk)) valid = 0;
    if(valid) {
        printf("Valid\n");
        printf("Total pairs = %d\n", match);
    }
    else printf("Invalid\n");
    release(stk);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}

Stack* newStack() {
    Stack *stk = malloc(sizeof(Stack));
    stk->data = malloc(sizeof(int));
    stk->capacity = 1;
    stk->top = -1;
    return stk;
}

bool empty(Stack *stk) {
    return stk->top < 0;
}

void check(Stack *stk) {
    if(stk->top == stk->capacity - 1) {
        int *tmp = realloc(stk->data, 2*stk->capacity*sizeof(int));
        if(tmp != NULL) {
            stk->data = tmp;
            stk->capacity *= 2;
        }
    }
}

void push(Stack *stk, int x) {
    check(stk);
    stk->data[++stk->top] = x;
}

void pop(Stack *stk){
    if(empty(stk)) return;
    stk->top--;
}

int top(Stack *stk) {
    if(empty(stk)) return -1;
    return stk->data[stk->top];
}

void release(Stack *stk) {
    if(stk != NULL) {
        if(stk->data != NULL) {
            free(stk->data);
        }
        free(stk);
    }
}