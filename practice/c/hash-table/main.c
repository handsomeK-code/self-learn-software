#include <stdio.h>

typedef struct HTable HTable;
typedef struct TableItem TableItem;

struct HTable{
    int *table;
    int size;

};
struct TableItem{
    int key;
    int value;
};

void init_table(HTable *self){
    self->table = calloc(16, sizeof(TableItem));
    self->size = 16;
}

int hash(int k, int m, int try){
    return ((k % m) + try - 1) % m;
}

void add(HTable *self, int k, int v){
    //check load factor first
    //what should the delete flag be
}
