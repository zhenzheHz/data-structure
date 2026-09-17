#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Stack {
    int *data;
    int capacity;
    int top;
};

void createS(struct Stack *stack) {
    stack->top = -1;
    stack->capacity = 1;
    stack->data = malloc(sizeof(int));
}

void StackFull(struct Stack *stack) {
    stack->data = realloc(stack->data, 2*stack->capacity*sizeof(int));
    stack->capacity *= 2;
}

bool IsFull(struct Stack *stack) {
    return stack->top >= stack->capacity-1;
}

bool IsEmpty(struct Stack *stack) {
    return stack->top < 0;
}

int Top(struct Stack *stack) {
    if(IsEmpty(stack)) return -1;
    return stack->data[stack->top];
}

void Push(struct Stack *stack, int val) {
    if(IsFull(stack)) StackFull(stack);
    stack->data[++stack->top] = val;
}

int Pop(struct Stack *stack) {
    if(stack->top == -1) return -1;
    return stack->data[stack->top--];
}

int main() {
    
    return 0;
}