typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    int size;
    struct Node *head;
} MyLinkedList;

Node* newNode(int val) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->data = val;
    new->next = NULL;
    return new;
}

MyLinkedList* myLinkedListCreate() {
    MyLinkedList *tmp = (MyLinkedList *) malloc(sizeof(MyLinkedList));
    tmp->size = 0;
    tmp->head = newNode(0);
    return tmp;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    if(index < 0 || index >= obj->size) return -1;
    Node *cur = obj->head->next;
    for(int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->data;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if(index > obj->size) return;
    if(index < 0) index = 0;
    Node *cur = obj->head, *new = newNode(val);
    for(int i = 0; i < index; i++) {
        cur = cur->next;
    }
    new->next = cur->next;
    cur->next = new;
    obj->size++;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    myLinkedListAddAtIndex(obj, 0, val);
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    myLinkedListAddAtIndex(obj, obj->size, val);
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if(index < 0 || index >= obj->size) return;
    Node *cur = obj->head;
    for(int i = 0; i < index; i++) {
        cur = cur->next;
    }
    Node *delNode = cur->next;
    cur->next = delNode->next;
    free(delNode);
    obj->size--;
}

void myLinkedListFree(MyLinkedList* obj) {
    Node *cur = obj->head;
    while(cur->next != NULL) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(obj);
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/