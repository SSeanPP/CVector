#include <stdio.h>
#include <stdlib.h>
/*Needs clear, shrink_to_fit*/

typedef struct {
    size_t size;
    size_t capacity;
    size_t element_size;
    void* vectorType;
} Vector;


typedef struct {
    int* data;
} Vector_int;

/*Initalising and resizing*/

void initaliseValues_int(int* data, size_t from, size_t to) {
    size_t i = 0;
    for (i = from; i < to; i++) {
        data[i] = 0;
    }
}

Vector* vectorInit_int() {
    size_t i = 0;
    Vector* v = malloc(sizeof(Vector));
    Vector_int* temp = malloc(sizeof(Vector_int));

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

    initaliseValues_int(temp->data, v->size, v->capacity);

    v->element_size = sizeof(int);
    v->vectorType = temp;
    return v;
}

void vector_resize_int(Vector* v, size_t newSize) {
    Vector_int* temp = (Vector_int*)v->vectorType;
    size_t i = 0;
    v->capacity =newSize;

    if (newSize >= v->capacity) {
        temp->data = realloc(temp->data, newSize * sizeof(int));
        if (!(temp->data)) {
            fprintf(stderr, "Error: realloc failed\n");
            exit(1);
        }
        initaliseValues_int(temp->data, v->capacity, newSize);
        v->capacity = newSize;
    }
    else {
        initaliseValues_int(temp->data, v->capacity, newSize);
        v->size = newSize;
    }
    
}

/*Element access*/
int* vector_data_int(Vector* v) {
    Vector_int* temp = (Vector_int*)v->vectorType;
    return temp->data;
}

int* vector_at_int(Vector* v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Error: Index %zu is out of bounds! (Size: %zu)\n", index, v->size);
        exit(1);
    }

    Vector_int* temp = (Vector_int*)v->vectorType;
    return temp->data[index];
}

const int* vector_front_int(Vector* v) {
    return vector_at_int(v, 0);
}

const int* vector_back_int(Vector* v) {
    return vector_at_int(v, (v->size - 1));
}

/*Adding and removing*/
void vector_push_back_int(Vector* v, int input) {
    Vector_int* temp = (Vector_int*)v->vectorType;
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

void vector_pop_back(Vector* v) {
    initaliseValues_int(vector_data_int(v), (v->size - 1), v->size);
    v->size--;
}

void vector_insert_int(Vector* v, size_t pos, int insertValue) {
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

int vector_empty_int(Vector* v) {
    if (v->size) {
        return 1;
    }
    else {
        return 0;
    }
}



int main(void) {
    int i = 0;
    Vector* v = vectorInit_int();

    for (i = 0; i < 6; i++) {
        vector_push_back_int(v, 15 * i);
    }


    vector_insert_int(v, 2, 100);
    vector_pop_back(v);
    vector_pop_back(v);
    vector_pop_back(v);
    vector_push_back_int(v, 43);

    for (i = 0; i < v->size; i++) {
        printf("%d\n", vector_at_int(v, i));
    }

    printf("Vector front: %d\n", vector_front_int(v));
    printf("Vector back: %d\n", vector_back_int(v));

    return 0;

}
