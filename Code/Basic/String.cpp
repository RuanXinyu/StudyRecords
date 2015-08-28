//
// Created by ruan on 15-7-21.
//

#include "String.h"
#include "gtest/gtest.h"

String::String(const char *str) {
    if (str == nullptr) {
        data = new char[1];
        data[0] = '\0';
    } else {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
}

String::String(const String &str) {
    data = new char[strlen(str.data) + 1];
    strcpy(data, str.data);
}

String::~String(void) {
    delete[] data;
}

String& String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] data;
        data = new char[strlen(rhs.data) + 1];
        strcpy(data, rhs.data);
    }
    return *this;
}

String String::operator+(const String &rhs) const{
    String str;
    str.data = new char[strlen(data) + strlen(rhs.data) + 1];
    strcpy(str.data, data);
    strcat(str.data, rhs.data);
    return str;
}

bool String::operator==(const String &rhs) const{
    return (strcmp(data, rhs.data) == 0);
}

char& String::operator[](int index) const {
    if (index >= 0 && index < strlen(data)) {
        return data[index];
    }
}

size_t String::size(void) {
    return strlen(data);
}

ostream& operator<<(ostream &out, String &str) {
    out << str.data;
    return out;
}

istream& operator>>(istream &in, String &str) {
    char tmp[512];
    in >> tmp;
    str.data = new char[strlen(tmp) + 1];
    strcpy(str.data, tmp);
    return in;
}

TEST(String, Class_String) {
    String a("a string. ");
    String b("b string. ");
    String c = b;
    String d = a + b;

    EXPECT_EQ(10, a.size());
    EXPECT_EQ(10, c.size());
    EXPECT_EQ(20, d.size());
    EXPECT_TRUE(c == b);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    a[0] = 'c';
    cout << a << endl;
}