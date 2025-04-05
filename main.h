
#ifndef MAIN_H
#define MAIN_H

struct Vector_int{
    size_t size;
    size_t capacity;
    size_t element_size;
    void* vectorType;
    void (*resize)(struct Vector_int*, size_t);
    int (*empty)(struct Vector_int*);
    void (*shrink_to_fit)(struct Vector_int*);
    int* (*data)(struct Vector_int*);
    int (*at)(struct Vector_int*, size_t);
    const int (*front)(struct Vector_int*);
    const int (*back)(struct Vector_int*);
    void (*push_back)(struct Vector_int*, int);
    void (*pop_back)(struct Vector_int*);
    void (*insert)(struct Vector_int*, size_t, int);
    void (*erase)(struct Vector_int*, size_t);
    void (*clear)(struct Vector_int*);
    void (*swap)(struct Vector_int*, struct Vector_int*);
};

#endif
