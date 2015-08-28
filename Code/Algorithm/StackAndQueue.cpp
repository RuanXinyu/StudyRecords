//
// Created by ruan on 15-7-18.
//

#include <gtest/gtest.h>
#include "iostream"
#include "StackAndQueue.h"
#include "stack"
#include "queue"
#include "exception"

using namespace std;

class LinkStack {
private:
    Node *s;
    int count;
public:
    LinkStack() {
        s = new Node;
        s->next = nullptr;
        count = 0;
    }

    void push(int data) {
        Node *tmp = new Node;
        tmp->value = data;
        tmp->next = s->next;
        s->next = tmp;
        ++count;
    }

    void pop() {
        if(s->next == nullptr) {
            return;
        }
        Node* tmp = s->next;
        s->next = s->next->next;
        --count;
        delete tmp;
    }

    bool empty() const {
        return (s->next == nullptr);
    }

    int& top() const {
        if (s->next == nullptr)
            throw "No data";
        return s->next->value;
    }

    int size() const {
        return count;
    }
};

class QueueStack {
private:
    queue<int> q1, q2;
public:
    void push(int data) {
        if (q1.empty()) {
            q2.push(data);
        } else {
            q1.push(data);
        }
    }

    void pop() {
        if (q2.empty() && !q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            q1.pop();
        } else if (q1.empty() && !q2.empty()) {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            q2.pop();
        }
    }

    bool empty() const {
        return (q2.empty() && q1.empty());
    }

    int size() const {
        return (q1.size() + q2.size());
    }

    int& top() {
        if (q2.empty() && !q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            int &data = q1.front();
            q2.push(data);
            q1.pop();
            return data;
        } else if (q1.empty() && !q2.empty()) {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            int &data = q2.front();
            q1.push(data);
            q2.pop();
            return data;
        } else {
            throw "No data";
        }
    }
};


TEST(StackFifo, Class_Stack) {
//    QueueStack s;
    LinkStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    EXPECT_EQ(4, s.top());
    EXPECT_EQ(4, s.size());
    EXPECT_FALSE(s.empty());

    s.pop();
    EXPECT_EQ(3, s.top());
    EXPECT_EQ(3, s.size());
    EXPECT_FALSE(s.empty());
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0, s.size());
    ASSERT_ANY_THROW(s.top());

    s.push(1);
    s.push(2);
    EXPECT_EQ(2, s.top());
    EXPECT_EQ(2, s.size());
    EXPECT_FALSE(s.empty());
}


/*********************************************************************************************/
/*********************************************************************************************/
class LinkQueue {
private:
    Node *head, *tail;
    int count;
public:
    LinkQueue() {
        head = tail = new Node;
        head->next = nullptr;
        count = 0;
    }

    void push(int data) {
        tail->next = new Node {data, nullptr};
        tail = tail->next;
        ++count;
    }

    void pop() {
        if (head->next != nullptr) {
            if (head->next == tail) {
                tail = head;
            }
            Node *tmp = head->next;
            head->next = head->next->next;
            delete tmp;
            --count;
        }
    }

    bool empty() const {
        return (head->next == nullptr);
    }

    int size() const {
        return count;
    }

    int& front() const {
        if (head->next == nullptr)
            throw "No data";
        return head->next->value;
    }

    int& back() const {
        if (head->next == nullptr)
            throw "No data";
        return tail->value;
    }
};

class StackQueue {
private:
    stack<int> s1, s2;
    void copy() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
    }
public:
    void push(int data) {
        s1.push(data);
    }


    void pop() {
        copy();
        if (!s2.empty()) {
            s2.pop();
        }
    }

    int& front() {
        copy();
        if (!s2.empty()) {
            return s2.top();
        } else {
            throw "No data";
        }
    }

    int& back() {
        if (s1.empty()) {
            if (s2.empty()) {
                throw "No data";
            } else {
                while (!s2.empty()) {
                    s1.push(s2.top());
                    s2.pop();
                }
                return s1.top();
            }
        } else {
            return s1.top();
        }
    }

    bool empty() {
        return (s1.empty() && s2.empty());
    }

    int size() {
        return (s1.size() + s2.size());
    }
};

TEST(StackFifo, Class_Queue) {
    StackQueue q;
//    LinkQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    EXPECT_EQ(1, q.front());
    EXPECT_EQ(4, q.back());
    EXPECT_EQ(4, q.size());
    EXPECT_FALSE(q.empty());

    q.pop();
    EXPECT_EQ(2, q.front());
    EXPECT_EQ(4, q.back());
    EXPECT_EQ(3, q.size());
    EXPECT_FALSE(q.empty());
    q.pop();
    q.pop();
    q.pop();
    q.pop();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(0, q.size());
    ASSERT_ANY_THROW(q.front());
    ASSERT_ANY_THROW(q.back());

    q.push(1);
    q.push(2);
    EXPECT_EQ(1, q.front());
    EXPECT_EQ(2, q.back());
    EXPECT_EQ(2, q.size());
    EXPECT_FALSE(q.empty());
}

/*********************************************************************************************/
/*********************************************************************************************/
class MinStack1 {
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


class MinStack2 {
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

class MinStack3 {
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

TEST(StackFifo, Class_MinStack1) {
    MinStack3 s;
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


/*********************************************************************************************/
/*********************************************************************************************/
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

/*********************************************************************************************/
/*********************************************************************************************/
void Stack_Reverse_Recursion(stack<int> &s) {
    if (s.size() < 2) {
        return;
    }

    int top = s.top();
    s.pop();

    Stack_Reverse_Recursion(s);
    int bottom = s.top();
    s.pop();

    Stack_Reverse_Recursion(s);
    s.push(top);
    Stack_Reverse_Recursion(s);

    s.push(bottom);
}

TEST(StackFifo, Stack_Reverse_Recursion) {
    stack<int> origin1, result1;
    Stack_Reverse_Recursion(origin1);
    EXPECT_TRUE(origin1 == result1);

    origin1.push(1);
    result1.push(1);
    Stack_Reverse_Recursion(origin1);
    EXPECT_TRUE(origin1 == result1);

    stack<int> origin2, result2;
    origin2.push(1);
    origin2.push(2);
    result2.push(2);
    result2.push(1);
    Stack_Reverse_Recursion(origin2);
    EXPECT_TRUE(origin2 == result2);

    stack<int> origin3, result3;
    for (int i = 1; i < 9; ++i) {
        origin3.push(i);
    }
    for (int i = 8; i > 0; --i) {
        result3.push(i);
    }
    Stack_Reverse_Recursion(origin3);
    EXPECT_TRUE(origin3 == result3);

    stack<int> origin4, result4;
    for (int i = 1; i < 10; ++i) {
        origin4.push(i);
    }
    for (int i = 9; i > 0; --i) {
        result4.push(i);
    }
    Stack_Reverse_Recursion(origin4);
    EXPECT_TRUE(origin4 == result4);
}

/*********************************************************************************************/
/*********************************************************************************************/
void Stack_SortAscend_Recursion(stack<int> &s) {
    if (s.size() < 2) {
        return;
    }

    int top = s.top();
    s.pop();

    Stack_SortAscend_Recursion(s);
    int max = s.top();
    if (max > top) {
        s.pop();
        s.push(top);
        Stack_SortAscend_Recursion(s);
    }
    s.push(max > top ? max : top);
}

TEST(StackFifo, Stack_Sort_Recursion) {
    stack<int> origin1, result1;
    Stack_SortAscend_Recursion(origin1);
    EXPECT_TRUE(origin1 == result1);

    origin1.push(1);
    result1.push(1);
    Stack_SortAscend_Recursion(origin1);
    EXPECT_TRUE(origin1 == result1);

    stack<int> origin2, result2;
    origin2.push(2);
    origin2.push(1);
    result2.push(1);
    result2.push(2);
    Stack_SortAscend_Recursion(origin2);
    EXPECT_TRUE(origin2 == result2);

    stack<int> origin21, result21;
    origin21.push(1);
    origin21.push(2);
    result21.push(1);
    result21.push(2);
    Stack_SortAscend_Recursion(origin21);
    EXPECT_TRUE(origin21 == result21);

    stack<int> origin3, result3;
    for (int i = 1; i < 9; ++i) {
        origin3.push(i);
        result3.push(i);
    }
    Stack_SortAscend_Recursion(origin3);
    EXPECT_TRUE(origin3 == result3);

    stack<int> origin4, result4;
    for (int i = 8; i > 0; --i) {
        origin4.push(i);
    }
    for (int i = 1; i < 9; ++i) {
        result4.push(i);
    }
    Stack_SortAscend_Recursion(origin4);
    EXPECT_TRUE(origin4 == result4);
}