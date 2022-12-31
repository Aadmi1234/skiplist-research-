#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
 
#define SKIPLIST_MAX_LEVEL 6
const int negative_inf = INT_MIN;
const int positive_inf = INT_MAX;

#ifdef laya1234
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("misc.txt", "w", stderr);
#endif

typedef struct node {
    int key;
    int value;  
    struct node **above;
} node;
 
typedef struct skiplist {
    int level;
    int size;
    struct node *lead;
} skiplist;
 
skiplist *skiplist_init(skiplist *list) {
    int i;
    node *header = (node *) malloc(sizeof(struct node));
    list->lead = header;
    header->key = positive_inf;
    header->above = (node **) malloc(
            sizeof(node*) * (SKIPLIST_MAX_LEVEL + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        header->above[i] = list->lead;
    }
 
    list->level = 1;
    list->size = 0;
 
    return list;
}
 
static int rand_level() {
    int level = 1;
    srand(time(NULL));
    while (rand()%2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    
    //while(rand() < RAND_MAX / 2 && level< SKIPLIST_MAX_LEVEL) level++;

    return level;
}
 
int skiplist_insert(skiplist *list, int key, int value) {
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *x = list->lead;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->above[i]->key < key)
            x = x->above[i];
        update[i] = x;
    }
    x = x->above[1];
 
    if (key == x->key) {
        x->value = value;
        return 0;
        // element already exists
    } 
    else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->lead;
            }
            list->level = level;
        }
 
        x = (node *) malloc(sizeof(node));
        x->key = key;
        x->value = value;
        x->above = (node **) malloc(sizeof(node*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->above[i] = update[i]->above[i];
            update[i]->above[i] = x;
        }
    }

    return 0;
}
 
node *skiplist_search(skiplist *list, int key) {
    node *x = list->lead;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->above[i]->key < key)
            x = x->above[i];
    }
    if (x->above[1]->key == key) {
        return x->above[1];
    } else {
        return NULL;
    }
    return NULL;
}
 
static void skiplist_node_free(node *x) {
    if (x) {
        free(x->above);
        free(x);
    }
}
 
int skiplist_delete(skiplist *list, int key) {
    int i;
    node *update[SKIPLIST_MAX_LEVEL + 1];
    node *x = list->lead;
    for (i = list->level; i >= 1; i--) {
        while (x->above[i]->key < key)
            x = x->above[i];
        update[i] = x;
    }
 
    x = x->above[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->above[i] != x)
                break;
            update[i]->above[1] = x->above[i];
        }
        skiplist_node_free(x);
 
        while (list->level > 1 && list->lead->above[list->level]
                == list->lead)
            list->level--;
        return 0;
    }
    return 1;
    //for attempt to remove non - existent node
}

static void skiplist_dump(skiplist *list) {
    node *x = list->lead;
    while (x && x->above[1] != list->lead) {
        printf("%d[%d]->", x->above[1]->key, x->above[1]->value);
        x = x->above[1];
    }
    printf("INF\n");
}

int main() {
    int arr[] = { 3, 6, 9, 2, 11, 72, 1, 4 };
    int i;
    skiplist list;
    skiplist_init(&list);
 
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_dump(&list);
 
    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111, 72 };
 
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        node *x = skiplist_search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not found\n", keys[i]);
        }
    }
 
    printf("Delete:--------------------\n");
    skiplist_delete(&list, 3);
    skiplist_delete(&list, 9);
    skiplist_delete(&list, 72);
    skiplist_delete(&list, 1);
    skiplist_dump(&list);
 
    return 0;
}