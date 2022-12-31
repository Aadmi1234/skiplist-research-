#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>


typedef node* nodepointer;
typedef struct{
    int key;
    nodepointer above;
    nodepointer below;
    nodepointer prev;
    nodepointer next;
}node;

const int negative_inf = INT_MIN;
const int positive_inf = INT_MAX;
nodepointer head;
nodepointer tail;

void initialize(nodepointer ptr){
    ptr->above = NULL;
    ptr->below = NULL;
    ptr->prev = NULL;
    ptr->next = NULL;
}

void insert(){
    head = (nodepointer)malloc(sizeof(node));
    tail = (nodepointer)malloc(sizeof(node));
    head->key = negative_inf;
    tail->key = positive_inf;
    initialize(&head);
    initialize(&tail);
}

nodepointer skipSearch(int key){
    nodepointer n = head;
    while(n->below!=NULL){
        n = n->below;
        
        while(key >= (n->next)->key){
            n = n->next;
        }
    }
    return n;
}