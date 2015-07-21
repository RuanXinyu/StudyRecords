## 检测push,pop序列是否一致
### 问题描述
> 输入两个整数序列。其中一个序列表示栈的push顺序，判断另一个序列有没有可能是对应的pop顺序，假设整数序列没有相同值

### 解决方案

**算法代码如下：**
```cpp
bool Stack_IsPopOrder(vector<int> &in, vector<int> &out) {
    if (in.size() == 0 || out.size() != in.size()) {
        return false;
    }

    stack<int> s;
    int inIndex, outIndex = 0;
    for (inIndex = 0; inIndex < in.size(); ++inIndex) {
        if (in[inIndex] != out[outIndex]) {
            s.push(in[inIndex]);
        } else {
            ++outIndex;
            while (!s.empty() && s.top() == out[outIndex]) {
                ++outIndex;
                s.pop();
            }
        }
    }
    return (inIndex == outIndex);
}
```

**测试用例如下：**
```cpp
TEST(StackFifo, Stack_IsPopOrder) {
    vector<int> in1 = {1, 2, 3, 4, 5};

    vector<int> out1 = {1, 2, 3, 4, 5};
    EXPECT_TRUE(Stack_IsPopOrder(in1, out1));
    vector<int> out2 = {2, 4, 3, 1, 5};
    EXPECT_TRUE(Stack_IsPopOrder(in1, out2));
    vector<int> out3 = {2, 4, 1, 3, 5};
    EXPECT_FALSE(Stack_IsPopOrder(in1, out3));
    vector<int> out4;
    EXPECT_FALSE(Stack_IsPopOrder(in1, out4));
    vector<int> out5 = {1, 2, 3};
    EXPECT_FALSE(Stack_IsPopOrder(in1, out5));

    vector<int> in2 = {1};
    vector<int> out6 = {1};
    EXPECT_TRUE(Stack_IsPopOrder(in2, out6));
    vector<int> out7 = {2};
    EXPECT_FALSE(Stack_IsPopOrder(in2, out7));
}
```
