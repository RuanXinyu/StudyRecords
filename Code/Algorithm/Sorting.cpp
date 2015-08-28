//
// Created by ruan on 15-5-22.
//

#include <stdio.h>
#include <gtest/gtest.h>
#include "../Common/utils.h"

/**
#### 排序分为四种：
* 交换排序： 包括冒泡排序，快速排序。
* 选择排序： 包括直接选择排序，堆排序。
* 插入排序： 包括直接插入排序，希尔排序。
* 合并排序： 合并排序。
**/

/****************************************I'm dividing line******************************************/
#define define_sort_data()                    \
int data[][10] = {														\
  {3, 44, 38, 5, 47, 15, 36, 26, 27, 2},  		\
  {2, 3, 5, 15, 26, 27, 36, 38, 44, 47},  		\
  {47, 44, 38, 36, 27, 26, 15, 5, 3, 2},  		\
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},         		\
  {1, 1, 1, 1, 2, 2, 1, 1, 1, 1},         		\
  {5, 1, 2, 3, 4, 5, 6, 7, 8, 9},         		\
  {1, 3, 4, 11, 9, 2, 0, 5, 7, 8},         		\
};																						\
const int result[][10] = {										\
  {2, 3, 5, 15, 26, 27, 36, 38, 44, 47},			\
  {2, 3, 5, 15, 26, 27, 36, 38, 44, 47},			\
  {2, 3, 5, 15, 26, 27, 36, 38, 44, 47},			\
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},							\
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2},							\
  {1, 2, 3, 4, 5, 5, 6, 7, 8, 9},							\
  {0, 1, 2, 3, 4, 5, 7, 8, 9, 11},							\
};

inline void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

/****************************************I'm dividing line******************************************/
void bubble_sort(int *ptr, int length) {
  int i, j;
  for(i = 0; i < length - 1; i++) {
    for (j = length - 1; j > i; j--) {
      if(ptr[j - 1] > ptr[j]) {
        swap(&ptr[j - 1], &ptr[j]);
      }
    }
  }
}

#if 1
TEST(algotithm_sorting_test, bubble_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    bubble_sort(data[i], sizeof(data[i]) / sizeof(data[i][0]));
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif

/****************************************I'm dividing line******************************************/
void quick_sort(int *ptr, int s, int e) {
  int i = s, j = e;

  if (s >= e)  return;

  while (i < j) {
    while (i < j && ptr[j] >= ptr[s]) j--;  //首先从右端往左端查找
    while (i < j && ptr[i] <= ptr[s]) i++;
    if (i < j) {
      swap(&ptr[i], &ptr[j]);
    }
  }
  swap(&ptr[i], &ptr[s]); //此时i==j
  quick_sort(ptr, s, i - 1);
  quick_sort(ptr, i + 1, e);
}

#if 1
TEST(algotithm_sorting_test, quick_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    quick_sort(data[i], 0, sizeof(data[i]) / sizeof(data[i][0]) - 1);
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif

/****************************************I'm dividing line******************************************/
void select_sort(int *ptr, int length) {
  int i, j, t;
  for(i = 0; i < length - 1; i++) {
    t = i;
    for (j = i + 1; j < length; j++) {
      if(ptr[j] < ptr[t]) {
        t = j;
      }
    }
    if (i != t) {
      swap(&ptr[i], &ptr[t]);
    }
  }
}

#if 1
TEST(algotithm_sorting_test, select_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    select_sort(data[i], sizeof(data[i]) / sizeof(data[i][0]));
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif

/****************************************I'm dividing line******************************************/
void heap_adjust(int *ptr, int p, int length) {
  int tmp = ptr[p], c = 2 * p + 1;
  while (c < length) {
    if (c + 1 < length && ptr[c + 1] > ptr[c]) {
      c++;
    }

    if (tmp >= ptr[c]) {
      break;
    }

    ptr[p] = ptr[c];
    p = c;
    c = 2 * p + 1;
  }
  ptr[p] = tmp;
}

void heap_sort(int *ptr, int length) {
  int i = 0;
  for (i = length / 2 - 1; i >= 0; i--) { //必须是由大到小的顺序
    heap_adjust(ptr, i, length);
  }

  for (i = length - 1; i > 0; --i) { //必须是由大到小的顺序
    swap(&ptr[0], &ptr[i]);
    heap_adjust(ptr, 0, i);
  }
}

#if 1
TEST(algotithm_sorting_test, heap_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    heap_sort(data[i], sizeof(data[i]) / sizeof(data[i][0]));
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif
/****************************************I'm dividing line******************************************/
/**
#### 插入排序
* 插入即表示将一个新的数据插入到一个有序数组中，并继续保持有序
* 平均时间复杂度：O(n2); 空间复杂度：O(1); 稳定性：稳定
**/
void insertion_sort(int *ptr, int length) {
  int tmp, i, j;
  for (i = 1; i < length; ++i) {
    tmp = ptr[i];
    for(j = i - 1; j >= 0 && tmp < ptr[j]; --j) {
      ptr[j + 1] = ptr[j];
    }
    ptr[j + 1] = tmp;
  }
}

#if 1
TEST(algotithm_sorting_test, insertion_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    insertion_sort(data[i], sizeof(data[i]) / sizeof(data[i][0]));
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif

/****************************************I'm dividing line******************************************/
void shell_sort(int *ptr, int length) {
  int step = length / 2, i, j, t;
  while (step >= 1) {
    for(i = step; i < length; i++) {
      t = ptr[i];
      for(j = i - step; j >= (i % step) && ptr[j] > t; j -= step) {
        ptr[j + step] = ptr[j];
      }
      ptr[j + step] = t;
    }
    step = step / 2;
  }
}

#if 1
TEST(algotithm_sorting_test, shell_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    shell_sort(data[i], sizeof(data[i]) / sizeof(data[i][0]));
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif

/****************************************I'm dividing line******************************************/
void merge_array(int *ptr, int left, int mid, int right) {
  int tmp[right - left + 1], m = left, n = mid, index = 0;
  while(m < mid && n <= right) {
    tmp[index++] = (ptr[m] > ptr[n]) ? ptr[n++] : ptr[m++];
  }

  while(m < mid) {
    tmp[index++] = ptr[m++];
  }

  while(n <= right) {
    tmp[index++] = ptr[n++];
  }

  for (index = 0; index < right - left + 1; ++index) {
    ptr[left + index] = tmp[index];
  }
}

void merge_sort(int *ptr, int left, int right) {
  int tmp = (left + right) / 2;
  if(left < right) {
    merge_sort(ptr, left, tmp);
    merge_sort(ptr, tmp + 1, right);
    merge_array(ptr, left, tmp + 1, right);
  }
}

#if 1
TEST(algotithm_sorting_test, merge_sort) {
  define_sort_data();
  int i = 0, count = sizeof(data) / sizeof(data[i]);

  for (i = 0; i < count; ++i) {
    merge_sort(data[i], 0, sizeof(data[i]) / sizeof(data[i][0]) - 1);
    EXPECT_TRUE(0 == memcmp(data[i], result[i], sizeof(data[i])));
  }
}
#endif