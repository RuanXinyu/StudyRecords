//
// Created by ruan on 15-8-3.
//

#include <glob.h>
#include <malloc.h>
#include "MyMalloc.h"


/*********************************************************************************************/
/*********************************************************************************************/
//编写支持对齐分配的malloc和free函数，分配地址时malloc函数返回的地址必须能被2的N次方整除
void* MyMalloc::aligned_malloc(size_t size, size_t align) {
    size_t offset = align - 1 + sizeof(void *);
    void *ptr = malloc(size + offset);
    if (ptr == NULL) {
        return NULL;
    }
    void **start = (void **)(((size_t)ptr + offset) & (~(align - 1)));
    start[-1] = ptr;
    return start;
}

void aligned_free(void *p) {
    free(((void **)p)[-1]);
}


/*********************************************************************************************/
/*********************************************************************************************/
//编写一个函数用来分配二位数组，并且可以通过arr[i][j]访问该内存
int** MyMalloc::array_malloc(size_t rows, size_t cols) {
    int **ptr = (int **)malloc(sizeof(int *) * rows + cols * rows * sizeof(int));
    if (ptr == NULL) return NULL;
    int *tmp = (int *)(ptr + rows);
    for (int i = 0; i < rows; ++i) {
        ptr[i] = tmp + cols * i;
    }
    return ptr;
}