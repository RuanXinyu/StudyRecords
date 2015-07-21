链表算法题目
====
## 题目列表
+ [将单链表反转](单链表反转.md)
+ [查找单链表中的倒数第K个结点](单链表中的倒数第K个结点.md)
+ [查找单链表的中间结点](单链表的中间结点.md)
+ [从尾到头打印链表](从尾到头打印链表.md)
+ [已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序](有序链表合并.md)
+ [判断一个单链表中是否有环](单链表中是否有环.md)
+ [判断两个单链表是否相交](两个单链表是否相交.md)
+ [求两个单链表相交的第一个节点](两个单链表相交的第一个节点.md)
+ [已知一个单链表中存在环，求进入环中的第一个节点](进入环型链表的第一个节点.md)
+ [给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted](删除链表指定节点.md)

## 基础函数
#### 函数声明
+ [typedef struct Node；]()
+ [void List_Init(Node nodeList[], int count, int baseVal = 0)；]()
+ [void List_InitLoop(Node nodeList[], int count, int loopNodeIndex, int baseVal = 0)；]()
+ [string List_GetListString(Node *head)；]()
+ [string List_GetSequenceString(int start, int end, int step)；]()


#### 函数实现
```cpp
typedef struct Node {
    int value;
    struct Node *next;
} Node;
```
```cpp
void List_Init(Node nodeList[], int count, int baseVal = 0) {
    for (int i = 0; i < count - 1; ++i) {
        nodeList[i].value = baseVal + i;
        nodeList[i].next = &nodeList[i + 1];
    }
    nodeList[count - 1].value = baseVal + count - 1;
    nodeList[count - 1].next = nullptr;
}
```
```cpp
void List_InitLoop(Node nodeList[], int count, int loopNodeIndex, int baseVal = 0) {
    for (int i = 0; i < count - 1; ++i) {
        nodeList[i].value = baseVal + i;
        nodeList[i].next = &nodeList[i + 1];
    }
    nodeList[count - 1].value = baseVal + count - 1;
    nodeList[count - 1].next = &nodeList[loopNodeIndex];
}
```
```cpp
string List_GetListString(Node *head) {
    Node *tmp = head;
    stringstream text;
    while (tmp != nullptr) {
        text << tmp->value << " ";
        tmp = tmp->next;
    }
    return text.str();
}
```
```cpp
string List_GetSequenceString(int start, int end, int step) {
    stringstream text;
    if(start <= end) {
        for (int i = start; i <= end; i += step) {
            text <<  i << " ";
        }
    } else {
        for (int i = start; i >= end; i -= step) {
            text << i << " ";
        }
    }
    return text.str();
}
```
