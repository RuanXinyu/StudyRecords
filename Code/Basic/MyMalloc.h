//
// Created by ruan on 15-8-3.
//

#ifndef LEARN_MYMALLOC_H
#define LEARN_MYMALLOC_H

class MyMalloc {
public:
    static void* aligned_malloc(size_t size, size_t align);
    static int** array_malloc(size_t rows, size_t cols);
};

#endif //LEARN_MYMALLOC_H
