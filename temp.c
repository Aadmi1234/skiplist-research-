#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
int main(){
    bool exit_control = true; char control = 0;
    while(exit_control){
        printf("\n\nEnter choice for respective operations: "
            "\n1) Insert Node"
            "\n2) Search Node"
            "\n3) Delete Node"
            "\n4) Print SkipList"
            "\n0)Press any other key to exit."
            "\n--> ");
        scanf(" %c",&control);
        switch(control){
            case '1': 
                printf("Print:----------------------------------\n");
                printf("Enter the key of the node to be inserted: ");
                int ins; scanf(" %d",&ins);
                skiplist_insert(&list, ins, ins);
                printf("\n\nNode inserted. Modified skiplist: \n\n");
                skiplist_dump(&list);
                break;
            
            case '2': 
                printf("Print:----------------------------------\n");
                printf("Enter the key of the node to be searched: ");
                int srch; scanf(" %d",&srch);
                node *x = skiplist_search(&list, srch);
                if (x) {
                    printf("key = %d, value = %d\n", srch, x->value);
                } else {
                    printf("key = %d, not found\n", srch);
                }
                break;

            case '3':
                printf("Delete:--------------------------------\n");
                printf("Enter the key of the node to be deleted: ");
                int del; scanf(" %d",&del);
                skiplist_delete(&list, 3);
                printf("\n\nNode removed. Modified skiplist: \n\n");
                skiplist_dump(&list);
                
                break;
            case '4':
                printf("Print:----------------------------------\n");
                skiplist_dump(&list);
                break;

            default : exit_control = false; 
        }
        // exit_control = false;
    }
    return 0;
}