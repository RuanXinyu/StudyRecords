### 实现包含min函数的栈
#### 问题描述
> 实现包含min函数的栈

#### 解决方案
##### 1. 实现一
**Tip:**开一个额外的栈minStack，每次元素进栈的时候将当前元素对应的最小值压入minStack栈，pop时两个栈都pop即可

**算法代码如下：**
```cpp
class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
public:
    void push(int data) {
        dataStack.push(data);
        minStack.push(minStack.empty() ? data : (minStack.top() > data ? data : minStack.top()));
    }

    void pop() {
        if(!dataStack.empty()) {
            dataStack.pop();
            minStack.pop();
        }
    }

    int min() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        throw  "No data";
    }

    int top() {
        if (!dataStack.empty()) {
            return dataStack.top();
        }
        throw  "No data";
    }
};
```

##### 2. 实现二
**Tip:** 该实现与实现一的不同之处是，只有待进栈的元素小于或者等于最小值时才将最小值压入minStack中，pop时则比较dataStack的数据是不是小于或者等于minStack中的栈顶，如果是则也pop出minStack栈顶元素。

**算法代码如下：**
```cpp
class MinStack {
private:
    stack<int> dataStack;
    stack<int> minStack;
public:
    void push(int data) {
        dataStack.push(data);
        if (minStack.empty()) {
            minStack.push(data);
        } else {
            if (data <= minStack.top()) {
                minStack.push(data);
            }
        }
    }

    void pop() {
        if(!dataStack.empty()) {
            if (dataStack.top() <= minStack.top()) {
                minStack.pop();
            }
            dataStack.pop();
        }
    }

    int min() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        throw  "No data";
    }

    int top() {
        if (!dataStack.empty()) {
            return dataStack.top();
        }
        throw  "No data";
    }
};
```


##### 3. 实现三
**Tip:** 该实现不使用额外的栈，而是将最小数信息存放在当前栈中，但是数据存的是数据与最小值的差值。如果待压入的值为最小值，则差值为0，在压入0之前现将之前的最小值压入栈内进行保存，每次pop时如果当前栈顶为0，则表示需要更新最小值。

**算法代码如下：**
```cpp
class MinStack {
private:
    stack<int> s;
    int minData;
public:
    void push(int data) {
        if (s.empty()) {
            s.push(data);
            s.push(0);
            minData = data;
        } else {
            if (data > minData) {
                s.push(data - minData);
            } else {
                s.push(minData);
                s.push(0);
                minData = data;
            }
        }
    }

    void pop() {
        if (!s.empty()) {
            if (s.top() == 0) {
                s.pop();
                minData = s.top();
                s.pop();
            } else {
                s.pop();
            }
        }
    }

    int min() {
        if (!s.empty()) {
            return minData;
        }
        throw  "No data";
    }

    int top() {
        if (!s.empty()) {
            return minData + s.top();
        }
        throw  "No data";
    }
};
```

**测试用例如下：**
```cpp
TEST(StackFifo, Class_MinStack) {
    MinStack s;
    s.push(20);
    s.push(21);
    EXPECT_EQ(21, s.top());
    EXPECT_EQ(20, s.min());
    s.push(11);
    s.push(12);
    EXPECT_EQ(12, s.top());
    EXPECT_EQ(11, s.min());
    s.push(11);
    s.push(13);
    EXPECT_EQ(13, s.top());
    EXPECT_EQ(11, s.min());

    s.pop();
    EXPECT_EQ(11, s.top());
    EXPECT_EQ(11, s.min());
    s.pop();
    EXPECT_EQ(12, s.top());
    EXPECT_EQ(11, s.min());
    s.pop();
    s.pop();
    EXPECT_EQ(21, s.top());
    EXPECT_EQ(20, s.min());
    s.pop();
    s.pop();
    s.pop();
    ASSERT_ANY_THROW(s.top());
    ASSERT_ANY_THROW(s.min());

    s.push(2);
    s.push(1);
    s.push(2);
    EXPECT_EQ(2, s.top());
    EXPECT_EQ(1, s.min());
}

```
