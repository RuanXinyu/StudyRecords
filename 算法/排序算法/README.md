排序算法的实现
====
## 说明
#### 复杂度统计
| 排序方法 | 最好情况     | 最坏情况    | 平均情况    | 空间复杂度  | 稳定性 |
|---------|------------|------------|------------|-----------|-------|
| 冒泡排序 | O（N）	   | O（N2）    | O（N2）     | O（1）     | 稳定   |
| 快速排序 | O（NlogN）  | O（N2）    | O（NlogN）  | O（NlogN） | 不稳定 |
| 选择排序 | O（N2）     | O（N2）    | O（N2）     | O（1）     | 不稳定 |
| 插入排序 | O（N）      | O（N2）    | O（N2）     | O（1）     | 稳定   |
| 希尔排序 |------------| O（NlogN） | O（NlogN）  | O（1）     | 不稳定 |
| 归并排序 | O（NlogN）  | O（NlogN） | O（NlogN）  | O（N）     | 稳定   |
| 堆排序   | O（NlogN）  | O（NlogN） | O（NlogN）  | O（1）     |不稳定  |
| 基数排序 | O（D(N+R)） | O（D(N+R)）| O（D(N+R)） | O（N + R） | 稳定   |

#### 其他说明
+ 冒泡排序在走一遍没有需要交换的元素时表示排序完成，因此最好的情况为O（N）的，但是下方的实现没有做此改进，因此最好的情况也是O（N2）的
+ 排序算法的稳定性就是能保证排序前2个相等的数其在序列的前后位置顺序和排序后它们两个的前后位置顺序相同(参见[网址](http://www.cnblogs.com/codingmylife/archive/2012/10/21/2732980.html))
+ 算法稳定的排序有** 冒泡排序， 插入排序， 归并排序， 基数排序**
+ 时间复杂度与初始化序列无关的时** 选择排序， 规定排序， 堆排序， 基数排序**
+ 二分查找最多需要比较`logN + 1`次



## 函数实现
### 二分查找
```cpp
int bSearch(int begin, int end, int e) {
    int mid, left = begin, right = end;
    while(left <= right) { // 这儿必须时<=, 否则单个元素会出错
        mid = (left + right) >> 1;
        // 有=表示取最左符合条件的数, 否则取最右符合条件的数
        if(num[mid] >= e) right = mid - 1;
        else left = mid + 1;
    }
    // 如果没有符合条件的数,则left表示返回右边与其接近的数的位置, right表示返回左边与其接近的数的位置
    return left;
}
```

### 冒泡排序
```cpp
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
```

### 快速排序
```cpp
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
```


### 选择排序
```cpp
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
```


### 堆排序
```cpp
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
```


### 插入排序
```cpp
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
```


### 希尔排序
```cpp
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
```


### 归并排序
```cpp
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
```

