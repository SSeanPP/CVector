#include <stdio.h>
#include <stdlib.h>

/*different branch*/
#define DEFINE_VECTOR(type)                 \
    typedef struct {                        \
        type *data;                         \
        size_t size;                        \
        size_t capacity;                    \
\
    } Vector_##type;                        \
    \
    void vector_##type##_init(Vector_##type *v) {  \
        v->size = 0;                         \
        v->capacity = 4;                     \
        v->data = malloc(v->capacity * sizeof(type));\
    }                                       \
    \
    void vector_##type##_resize(Vector_##type *v){\
        v->capacity *=2;\
        v->data = realloc(v->data, v->capacity * sizeof(type));\
    }\
    void vector_##type##_push_back(Vector_##type *v, type value) { \
        if (v->size == v->capacity) {       \
            vector_##type##_resize(v); \
        }                                   \
        v->data[v->size++] = value;         \
    }                                       \
    \
    void vector_##type##_pop_back (Vector_##type *v) {\
        v->size--;\
        \
    }\
    \
    type vector_##type##_at (Vector_##type *v, unsigned int index) { \
        if (index >= v->size) {             \
            return (type)0;                    \
        }                                   \
        return *((type*)((char*)v->data + (index * sizeof(type)))); \
    }\
    \
    type* vector_##type##_returnData(Vector_##type *v) {\
        return v->data;\
    }\
    \
    void vector_##type##_free(Vector_##type *v) { \
        free(v->data);                      \
        v->data = NULL;                     \
        v->size = 0;                        \
        v->capacity = 0;                    \
    }\

DEFINE_VECTOR(int)
DEFINE_VECTOR(float)
DEFINE_VECTOR(char)

int main(void) {
    Vector_int vec;
    Vector_float vecf;
    Vector_char vecc;
    size_t testing;
    vector_int_init(&vec);

    vector_int_push_back(&vec, 10);
    vector_int_push_back(&vec, 20);
    vector_int_push_back(&vec, 30);
    vector_int_push_back(&vec, 30);
    vector_int_push_back(&vec, 50);
    vector_int_push_back(&vec, 60);
    vector_int_pop_back(&vec);

    vector_float_init(&vecf);
    vector_float_push_back(&vecf, 10.05);
    vector_float_push_back(&vecf, 20.05);
    vector_float_push_back(&vecf, 30.05);

    vector_char_init(&vecc);
    vector_char_push_back(&vecc, 'A');
    vector_char_push_back(&vecc, 'B');
    vector_char_push_back(&vecc, 'C');
    printf("test");

    for (testing = 0; testing < vec.size; testing++) {
        printf("%d ", vector_int_at(&vec, testing));
    }

    for (testing = 0; testing < vecf.size; testing++) {
        printf("%f ", vector_float_at(&vecf, testing));
    }

    for (testing = 0; testing < vecc.size; testing++) {
        printf("%c ", vector_char_at(&vecc, testing));
    }

    vector_float_free(&vecf);
    vector_int_free(&vec);
    vector_char_free(&vecc);
    return 0;

}