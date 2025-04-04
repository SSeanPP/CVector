#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t capacity;
    size_t element_size;
    void* vectorType;
} Vector;


typedef struct {
    int* data;
} Vector_int;

Vector* vectorInit_int() {
    Vector* v = malloc(sizeof(Vector));
    Vector_int* temp = malloc(sizeof(Vector_int));
    if (!v) {
        fprintf(stderr, "Error: v is NULL, failed allocation\n");
        exit(1);
    }
    if (!temp) {
        fprintf(stderr, "Error: temp->data is NULL, failed allocation\n");
        exit(1);
    }
    v->size = 0;
    v->capacity = 4;
    temp->data = malloc(v->capacity * sizeof(int));
    v->element_size = sizeof(int);
    v->vectorType = temp;
    return v;
}

void vector_resize_int(Vector* v) {
    Vector_int* temp = (Vector_int*)v->vectorType;
    int* data = temp->data;
    v->capacity *= 2;

    temp->data = realloc(temp->data, v->capacity * v->element_size);
}

Vector_int* vector_returnTypeVector(Vector* v) {
    return v->vectorType;
}

int* vector_returnData(Vector_int* v) {
    return v->data;
}

int vector_at_int(Vector* v, size_t index) {
    /*return *((int*)((char*)v->vectorType + (index * v->element_size)))*/
    if (index >= v->size) {
        fprintf(stderr, "Error: Index %zu is out of bounds! (Size: %zu)\n", index, v->size);
    }
    Vector_int* temp = (Vector_int*)v->vectorType;
    return temp->data[index];
}

void vector_push_back_int(Vector* v, int input) {
    Vector_int* temp = (Vector_int*)v->vectorType;
    if (v->vectorType == NULL)
    {
        fprintf(stderr, "This is an error message.\n");
        exit(1);
    }

    if (v->size == v->capacity) {
        vector_resize_int(v);
    }

    /*char* address = data + (v->size * v->element_size);*/
    temp->data[v->size] = input;
    v->size += 1;
}

void vector_insert_int(Vector* v) {

}

void vector_pop_back(Vector* v) {
    v->size--;
}




int main(void) {
    int i = 0;
    Vector* v = vectorInit_int();
    
    for (i = 0; i < 6; i++) {
        vector_push_back_int(v, 15*i);
        
    }

    vector_pop_back(v);

    for (i = 0; i < v->size; i++) {
        printf("%d\n", vector_at_int(v, i));
    }

    return 0;

}
