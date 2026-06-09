#include <stdio.h>

typedef struct Vector{

    int *array;
    int size;
}Vector;

void init_vector(Vector *vector) {
    vector->array = calloc(16 * sizeof(int));
    vector->size = 16;
}

int size(Vector *vector) {
    return vector->size;
}