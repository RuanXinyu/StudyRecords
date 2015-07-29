String类的实现
====
## 实现说明
1. 拷贝构造函数，运算符重载中是可以调用参数对象中的私有成员变量的,但是不可以调用基类的私有数据成员。


#### 默认构造函数
C++中定义变量`String str;`调用的就是默认构造函数，没有`String str();`这种方式定义变量，但是C#可以。
+ `String(const char *str = nullptr);`所示的构造函数既可以当做赋值构造也可以当做默认构造函数。
+ 带有默认参数的函数只需要在声明的时候声明，在定义的时候时不需要写上的。

#### 拷贝构造函数
拷贝构造函数声明为：`String(const String& str);`，做一下几点说明：
+ 拷贝构造函数是没有返回值的
+ 拷贝构造函数的参数必须是引用类型，否则会进入死循环，同时最好加上const修饰
+ 拷贝构造函数有深拷贝和浅拷贝之说，在需要动态分配内存的类中一定要做深拷贝

#### 重载赋值运算符
赋值运算符的函数声明为：`String& operator=(const String& rhs);`，做以下几点说明：
+ 返回值为引用类型，否则不支持连续赋值操作
+ 参数为const型的引用类型，如果不为const类型的话将const类型的对象赋值给非const类型的对象时会报错，因为const变量是不可以随意转换为非const类型的
+ 判断参数和当前实例是不是相等，如果相等返回当前实例即可，否则可能会出现错误
+ 记得在分配新的内存之前先释放内存，否则会造成内存泄露

#### 重载+运算符/重载==运算符
加号运算符的函数声明为：`String operator+(const String& rhs) const;`，做以下几点说明：
+ 返回值不是引用类型
+ 函数参数为const型的引用参数
+ 函数修饰为const类型，以防止函数改变成员变量

#### 重载[]运算符
[]运算符的函数声明为：`char& operator[](int index) const;`，做以下几点说明：
+ 返回值为引用类型
+ 函数修饰为const类型，以防止函数改变成员变量

#### 流运算符重载
流运算符重载函数声明为：`friend ostream& operator<<(ostream &out, String &str);`和`friend istream& operator>>(istream &in, String &str);`，做以下几点说明：
+ 函数为友元函数，而友元函数既不是private类型，也不是public类型
+ 返回值为引用类型，否则不支持连续使用>>或<<
+ 函数的第一个参数为ostream或istream的引用类型，不需要声明为const类型，因为会对其进行改变
+ 友元函数的实现是不需要指定类的作用域的


## 代码实现
```cpp
class String {
    friend ostream& operator<<(ostream &out, String &str);
    friend istream& operator>>(istream &in, String &str);
private:
    char *data;

public:
    String(const char *str = nullptr);
    String(const String& str);
    ~String(void);

    String& operator=(const String& rhs);
    String operator+(const String& rhs) const;
    bool operator==(const String& rhs) const;
    char& operator[](int index) const;
    size_t size(void);
};

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
```
## 测试用例
```cpp
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
```