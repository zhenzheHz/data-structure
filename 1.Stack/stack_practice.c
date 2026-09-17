// Problem : https://zerojudge.tw/ShowProblem?problemid=b838
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Stack {
    int *data;
    int capacity;
    int top;
};

void createS(struct Stack *stk) {
    stk->data = malloc(sizeof(int));
    stk->capacity = 1;
    stk->top = - 1;
}

bool IsFull(struct Stack *stk) {
    return stk->top == stk->capacity - 1;
}

bool IsEmpty(struct Stack *stk) {
    return stk->top < 0;
}

void StackFull(struct Stack *stk) {
    if(IsFull(stk)) {
        int *tmp = realloc(stk->data, 2*stk->capacity*sizeof(int));
        if(tmp != NULL) {
            stk->data = tmp;
            stk->capacity *= 2;
        }
    }
}

int Top(struct Stack *stk) {
    if(!IsEmpty(stk)) return stk->data[stk->top];
    return -1;
}

void Push(struct Stack *stk, int val) {
    if(IsFull(stk)) StackFull(stk);
    stk->data[++stk->top] = val;
}

int Pop(struct Stack *stk) {
    if(IsEmpty(stk)) return -1;
    return stk->data[stk->top--];
}

int main() {
    int T,match;
    char line[25];
    scanf("%d", &T);
    while(T--) {
        match = 0;
        scanf("%s", line);
        struct Stack stk;
        createS(&stk);
        int len = strlen(line);
        for(int i = 0; i < len; i++) {
            if(line[i] == '(') {
                Push(&stk, 1);
            }
            if(line[i] == ')') {
                if(IsEmpty(&stk)) {
                    match = 0;
                    break;
                }
                else {
                    match++;
                    Pop(&stk);
                }
            }
        }
        if(!IsEmpty(&stk)) match = 0;
        printf("%d\n", match);
        free(stk.data);
        stk.data = NULL;
    }
    return 0;
}
