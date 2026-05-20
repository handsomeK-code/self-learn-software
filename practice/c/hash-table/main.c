#include <stdio.h>
#include <stdlib.h>

typedef struct HTable HTable;
typedef struct TableItem TableItem;

typedef enum {
    DELETED,
    OCCUPIED
}ItemState;

struct HTable{
    TableItem **table;
    int currKeys;
    int tableSize;

};

struct TableItem{
    int key;
    int value;
    ItemState state;
};

void init_table(HTable *self){
    self->table = calloc(16, sizeof(TableItem *));

    if (self->table == NULL) {
        printf("memory allocation failed");
        exit(1);
    }
    self->currKeys = 0;
    self->tableSize = 16;
}

int hash(int k, int m, int try){
    return ((k % m) + try - 1) % m;
}

void resize_table(HTable *self, float resize_factor);

int add(HTable *self, int key, int v){
    float loadFactor = (float)self->currKeys / self->tableSize;
    int deletedSlot = -1;

    if (loadFactor >= 0.5) {
        resize_table(self, 2.0);
    }

    for(int try = 1; try <= self->tableSize; try++) {
        int index = hash(key, self->tableSize, try);

        if (self->table[index] == NULL) {
            if (deletedSlot == -1) {
                TableItem *item = calloc(1, sizeof(TableItem));
                if (item == NULL) {
                    printf("fail to allocate memory");
                    return -1;
                }
                item->key = key;
                item->state = OCCUPIED;
                item->value = v;
                self->table[index] = item;
                self->currKeys++;
                return 0;
            } else {
                self->table[deletedSlot]->key = key;
                self->table[deletedSlot]->state = OCCUPIED;
                self->table[deletedSlot]->value = v;
                self->currKeys++;
                return 0;
            }
        }

        if (self->table[index]->state == DELETED){
            if (deletedSlot == -1) {
                deletedSlot = index;
            }
        }

        if (self->table[index]->state == OCCUPIED && self->table[index]->key == key){
            self->table[index]->value = v;
            return 0;
        }
    }

    self->table[deletedSlot]->key = key;
    self->table[deletedSlot]->state = OCCUPIED;
    self->table[deletedSlot]->value = v;
    self->currKeys++;
    return 0;
}

void resize_table(HTable *self, float resize_factor){
    //rehash needed
    TableItem **new_table = calloc(self->tableSize * resize_factor, sizeof(TableItem *));
    if (new_table == NULL) {
        printf("fail to allocate memory");
        exit(-1);
    }

    TableItem **old_table = self->table;
    int old_size = self->tableSize;
    self->table = new_table;
    self->tableSize *= resize_factor;
    self->currKeys = 0;



    for (int i = 0; i < old_size; i++) {
        if (old_table[i] != NULL && old_table[i]->state == OCCUPIED) {
            add(self, old_table[i]->key, old_table[i]->value);
            free(old_table[i]);
        }

        if (old_table[i] != NULL) {
            free(old_table[i]);
        }
    }

    free(old_table);
}

int exist(HTable *self, int key) {
    for (int try = 1; try <= self->tableSize; try++) {
        int index = hash(key, self->tableSize, try);

        if (self->table[index] == NULL) {
            return 0;
        }

        if (self->table[index]->state == DELETED) {
            continue;
        }

        if (self->table[index]->key == key) {
            return 1;
        }
    }

    return 0;
}

TableItem * get(HTable *self, int key) {
    for (int try = 1; try <= self->tableSize; try++) {
        int index = hash(key, self->tableSize, try);

        if (self->table[index] == NULL) {
            return NULL;
        }

        if (self->table[index]->state == DELETED) {
            continue;
        }

        if (self->table[index]->key == key) {
            return self->table[index];
        }
    }

    return NULL;
}

int remove_key(HTable *self, int key) {
    TableItem* currentItem = get(self, key);

    if (currentItem == NULL) {
        return -1;
    }

    currentItem->state = DELETED;
    self->currKeys--;
    return 0;
}

//test function
int main() {
    HTable test_table;

    init_table(&test_table);

    for(int i = 0; i <= 9; i++) {
        add(&test_table, i, i);
    }


    int test_key = 5;
    TableItem *test_item = get(&test_table, test_key);
    printf("Test Key\n");
    printf("%d\n", test_key);

    printf("Output Key\n");
    printf("%d\n", test_item->key);
    printf("Output Value");
    printf("%d\n", test_item->value);
}
