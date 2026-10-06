#include <stdio.h>
#include <stdlib.h>

typedef struct Vector{

    int *array;
    int size;
    int capacity;
}Vector;

void init_vector(Vector *vector) {
    vector->array = calloc(16, sizeof(int));
    vector->size = 0;
    vector->capacity = 16;
}

int vector_size(Vector *vector) {
    return vector->size;
}

int vector_capacity(Vector *vector) {
    return vector->capacity;
}

int vector_is_empty(Vector *vector) {
    return vector->size == 0;
}

int vector_at(Vector *vector, int pos) {
    if (pos < 0 || vector->size <= pos) {
        printf("Out of bound");
        return -1;
    }

    return *(vector->array + pos);
}

int vector_resize(Vector *vector, float resize_factor) {
   int *new_array = calloc(vector->capacity * resize_factor, sizeof(int));
   if (new_array == NULL) {
        printf("Fail to callocate new memory");
        return -1;
   }

   // relloc should better but I want to practice 
   int *input_array = new_array;
    for (int *item = vector->array; item < vector->array + vector->size; item++){
        *input_array = *item;
        input_array++;
    }

    free(vector->array);

    vector->array = new_array;
    vector->capacity = vector->capacity * resize_factor;
    return 0;
}

int vector_push(Vector *vector, int item) {
    if (vector->size == vector->capacity) {
        int err = vector_resize(vector, 2.0);
        if (err == -1) {
            printf("fail to resize");
            return -1;
        }

    }

    *(vector->array + vector->size) = item;
    vector->size++;

    return 0;
}

int vector_insert(Vector *vector, int item, int index) {

    if (index < 0 || vector->size < index) {
        printf("Out of bound");
        return -1;
    }

    if (vector->size == vector->capacity) {
        int err = vector_resize(vector, 2.0);
        if (err == -1) {
            printf("fail to resize");
            return -1;
        }
    }

    for (int *start = vector->array + vector->size; start>vector->array + index; start--) {
        *(start) = *(start - 1);
    }

    vector->array[index] = item;
    vector->size++;
    return 0;
}

int vector_prepend(Vector *vector, int item) {
    int err = vector_insert(vector, item, 0);
    if (err == 0) {
        return 0;
    }

    return -1;
}

int vector_pop(Vector *vector) {
    if (vector->size == 0) {
        printf("Empty array");
        return -1;
    }
    int result = *(vector->array + vector->size - 1);

    vector->size--;

    if (vector-> size <= vector->capacity / 4) {
        int err = vector_resize(vector, 0.5);
        if (err == 0) {
            return result;
        }
        printf("fail to resize");
        return -1;
    }

    return result;
}

int vector_delete(Vector *vector,int index) {
    if (index < 0 || vector->size <= index) {
        printf("Out of bound");
        return -1;
    }

    for (int i = index; i < vector->size - 1; i++ ) {
        vector->array[i] = vector->array[i + 1];
    }

    vector->size--;

    if (vector-> size <= vector->capacity / 4) {
        int err = vector_resize(vector, 0.5);
        if (err == 0) {
            return 0;
        }
        printf("fail to resize");
        return -1;
    }

    return 0;
}

int vector_remove(Vector *vector, int item) {

    int w = 0;
    for (int r = 0; r < vector->size; r++) {
        if (vector->array[r] != item) {
            vector->array[w] = vector->array[r];
            w++;
        }
    }

    if (w == vector->size) {
        printf("not found");
        return -1;
    }else {
        vector->size = w;
        if (vector->size <= vector->capacity / 4) {
            int err = vector_resize(vector, 0.5);
            if (err == 0) {
                return 0;
            }
            printf("fail to resize");
            return -1;
        }

        return 0;
    }
}

int vector_find(Vector *vector, int item) {
    for (int i = 0; i < vector->size; i++) {
        if (vector->array[i] == item) {
            return i;
        }
    }

    return -1;
}

