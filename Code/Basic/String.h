//
// Created by ruan on 15-7-21.
//

#ifndef LEARN_STRING_H
#define LEARN_STRING_H
#include "iostream"
using namespace std;

class String {
    friend ostream& operator<<(ostream &out, String &str); //记住函数声明,参数不为const，因为内部会改变
    friend istream& operator>>(istream &in, String &str);  //记住函数声明
private:
    char *data;

public:
    String(const char *str = nullptr);
    String(const String& str);  //无返回值，参数必须为引用
    ~String(void);

    String& operator=(const String& rhs); //返回值必须为引用
    String operator+(const String& rhs) const; //返回值不是引用类型，函数为const类型
    bool operator==(const String& rhs) const;
    char& operator[](int index) const;
    size_t size(void);
};

#endif //LEARN_STRING_H
