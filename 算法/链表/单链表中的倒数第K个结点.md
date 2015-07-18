### 查找单链表中的倒数第K个结点
#### 问题描述
> 查找单链表中的倒数第K个结点

#### 解决方案
**Tip:**使用两个指针，先让前面的指针走到正向第k个结点，这样前后两个指针的距离差是k-1，之后前后两个指针一起向前走，前面的指针走到最后一个结点时，后面指针所指结点就是倒数第k个结点

**算法代码如下：**
```cpp
Node* List_FindNodeByIndexFromBehind(Node *head, int index) {
    Node *ahead = head, *behind = head;
    if (index <= 0 || head == nullptr) {
        return nullptr;
    }

    while (index-- > 1 && ahead != nullptr) {
        ahead = ahead->next;
    }

    if (index > 1) return nullptr;

    while (ahead->next != nullptr) {
        ahead = ahead->next;
        behind = behind->next;
    }
    return behind;
}
```

**测试用例如下：**
```cpp
TEST(LinkedList, List_FindNodeByIndexFromBehind) {
    Node nodeList[10];

    EXPECT_TRUE(nullptr == List_FindNodeByIndexFromBehind(nullptr, 5));

    List_Init(nodeList, 10);
    EXPECT_TRUE(nullptr == List_FindNodeByIndexFromBehind(nodeList, 0));
    EXPECT_TRUE(nullptr == List_FindNodeByIndexFromBehind(nodeList, 20));
    EXPECT_TRUE(9 == List_FindNodeByIndexFromBehind(nodeList, 1)->value);
    EXPECT_TRUE(5 == List_FindNodeByIndexFromBehind(nodeList, 5)->value);
    EXPECT_TRUE(0 == List_FindNodeByIndexFromBehind(nodeList, 10)->value);
}
```
