#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/*Needs erase, shrink_to_fit*/

typedef struct {
    int* data;
} Vector_int_inner;

/*Initialising and resizing*/

void initialiseValues_int(int* data, size_t from, size_t to) {
    size_t i = 0;
    for (i = from; i < to; i++) {
        data[i] = 0;
    }
}

void vector_resize_int(struct Vector_int* v, size_t newSize) {
    Vector_int_inner* temp = (Vector_int_inner*)v->vectorType;
    v->capacity =newSize;

    if (newSize >= v->capacity) {
        temp->data = realloc(temp->data, newSize * sizeof(int));
        if (!(temp->data)) {
            fprintf(stderr, "Error: reallocate failed\n");
            exit(1);
        }
        initialiseValues_int(temp->data, v->capacity, newSize);
        v->capacity = newSize;
    }
    else {
        initialiseValues_int(temp->data, v->capacity, newSize);
        v->size = newSize;
    }
}

int vector_empty_int(struct Vector_int* v) {
    if (v->size) {
        return 1;
    }
    else {
        return 0;
    }
}

void vector_shrink_to_fit_int(struct Vector_int* v) {
    Vector_int_inner* temp = (Vector_int_inner*)v->vectorType;
    temp->data = realloc(temp->data, v->size * sizeof(int));
    if (!(temp->data)) {
        fprintf(stderr, "Error: reallocate failed\n");
        exit(1);
    }

    v->capacity = v->size;
}

/*Element access*/
int* vector_data_int(struct Vector_int* v) {
    Vector_int_inner* temp = (Vector_int_inner*)v->vectorType;
    return temp->data;
}

int vector_at_int(struct Vector_int* v, size_t index) {
    Vector_int_inner* temp = (Vector_int_inner*)v->vectorType;

    if (index >= v->size) {
        fprintf(stderr, "Error: Index %zu is out of bounds! (Size: %zu)\n", index, v->size);
        exit(1);
    }
    return temp->data[index];
}

const int vector_front_int(struct Vector_int* v) {
    return vector_at_int(v, 0);
}

const int vector_back_int(struct Vector_int* v) {
    return vector_at_int(v, (v->size - 1));
}

/*Adding and removing*/
void vector_push_back_int(struct Vector_int* v, int input) {
    Vector_int_inner* temp = (Vector_int_inner*)v->vectorType;
    if (v->vectorType == NULL)
    {
        fprintf(stderr, "This is an error message.\n");
        exit(1);
    }

    if (v->size == v->capacity) {
        vector_resize_int(v, (v->capacity * 2));
    }

    temp->data[v->size] = input;
    v->size += 1;
}

void vector_pop_back_int(struct Vector_int* v) {
    initialiseValues_int(vector_data_int(v), (v->size - 1), v->size);
    v->size--;
}

void vector_insert_int(struct Vector_int* v, size_t pos, int insertValue) {
    int previous = insertValue;
    int next;
    int* data = vector_data_int(v);
    size_t i = 0;

    if (pos > (v->size + 1)) {
        fprintf(stderr, "Error: Position %zu is out of bounds! (Size: %zu)\n", pos, v->size);
        exit(1);
    }

    if (v->size == v->capacity) {
        vector_resize_int(v, (v->capacity * 2));
    }

    v->size++;

    for (i = pos; i < v->size; i++) {
        next = vector_at_int(v, i);
        data[i] = previous;
        previous = next;
    }
}

void vector_erase_int(struct Vector_int* v, size_t pos) {
    int previous = 0;
    int next;
    int* data = vector_data_int(v);
    size_t i = 0;

    if (pos > (v->size)) {
        fprintf(stderr, "Error: Position %zu is out of bounds! (Size: %zu)\n", pos, v->size);
        exit(1);
    }

    for (i = (v->size - 1); i > pos; i--) {
        next = vector_at_int(v, i);
        data[i] = previous;
        previous = next;
    }

    v->size--;
}

void vector_clear_int(struct Vector_int* v) {
    v->size = 0;
    initialiseValues_int(vector_data_int(v), v->size, v->capacity);
}

void vector_swap_int(struct Vector_int* a, struct Vector_int* b) {
    struct Vector_int temp;
    temp.vectorType = b->vectorType;
    b->vectorType = a->vectorType;
    a->vectorType = temp.vectorType;
}

struct Vector_int* vectorInit_int() {
    size_t i = 0;
    struct Vector_int* v = malloc(sizeof(struct Vector_int));
    Vector_int_inner* temp = malloc(sizeof(Vector_int_inner));

    if (!v) {
        fprintf(stderr, "Error: v is NULL, failed allocation\n");
        exit(1);
    }
    if (!temp) {
        fprintf(stderr, "Error: temp is NULL, failed allocation\n");
        exit(1);
    }

    v->size = 0;
    v->capacity = 4;
    temp->data = malloc(v->capacity * sizeof(int));

    if (!temp->data) {
        fprintf(stderr, "Error: temp->data is NULL, failed allocation\n");
        exit(1);
    }

    initialiseValues_int(temp->data, v->size, v->capacity);

    v->element_size = sizeof(int);
    v->vectorType = temp;

    v->resize = vector_resize_int;
    v->empty = vector_empty_int;
    v->shrink_to_fit = vector_shrink_to_fit_int;
    v->data = vector_data_int;
    v->at = vector_at_int;
    v->front = vector_front_int;
    v->back = vector_back_int;
    v->push_back = vector_push_back_int;
    v->pop_back = vector_pop_back_int;
    v->insert = vector_insert_int;
    v->erase = vector_erase_int;
    v->clear = vector_clear_int;
    v->swap = vector_swap_int;

    return v;
}

int main(void) {
    int i = 0;
    struct Vector_int* v = vectorInit_int();

    for (i = 0; i < 6; i++) {
        v->push_back(v, i);
    }

    v->erase(v, 3);

    for (i = 0; i < v->size; i++) {
        printf("%d\n", v->at(v, i));
    }

    v->shrink_to_fit(v);

    printf("Vector front: %d\n", v->front(v));
    printf("Vector back: %d\n", v->back(v));
    printf("Vector cap: %lld, Vector size: %lld\n", v->capacity, v->size);

    return 0;

}
