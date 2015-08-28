//
// Created by ruan on 15-7-22.
//

#include <assert.h>
#include <gtest/gtest.h>
#include "StdFun.h"

using namespace std;

size_t StdFun::strlen(const char *s) {
    assert(s != nullptr);
    size_t count = 0;
    while (*s++ != '\0') {
        ++count;
    }
    return count;
}

TEST(StdFun, strlen) {
    EXPECT_EQ(0, StdFun::strlen(""));
    EXPECT_EQ(1, StdFun::strlen("1"));
    EXPECT_EQ(9, StdFun::strlen("123456789"));
}


/*********************************************************************************************/
/*********************************************************************************************/

char* StdFun::strcpy(char *s1, const char *s2) {
    assert(s1 != nullptr && s2 != nullptr);
    char *s = s1;
    while ((*s++ = *s2++) != 0);
    return (s1);
}

TEST(StdFun, strcpy) {
    char dst[10] = "987654321";

    EXPECT_STREQ("123456789", StdFun::strcpy(dst, "123456789"));
    EXPECT_STREQ("abcde", StdFun::strcpy(dst, "abcde"));
    EXPECT_STREQ("", StdFun::strcpy(dst, ""));
}

/*********************************************************************************************/
/*********************************************************************************************/
char* StdFun::strncpy(char *s1, const char *s2, size_t n) {
    assert(s1 != nullptr && s2 != nullptr);
    char *s = s1;
    // 不能写成 while (n-- > 0 && *s2 != '\0')方式，因为当n = 0时会出现异常
    while (n > 0 && *s2 != '\0') {
        *s++ = *s2++;
        --n;
    }
    while (n-- > 0) {
        *s++ = '\0';
    }
    return (s1);
}

TEST(StdFun, strncpy) {
    char dst[10] = "";

    for (int i = 0; i < 10; ++i) dst[i] = 0;
    EXPECT_STREQ("123456789", StdFun::strncpy(dst, "123456789", 10));
    for (int i = 0; i < 10; ++i) dst[i] = 0;
    EXPECT_STREQ("12345", StdFun::strncpy(dst, "123456789", 5));
    for (int i = 0; i < 10; ++i) dst[i] = 0;
    EXPECT_STREQ("", StdFun::strncpy(dst, "123456789", 0));
    for (int i = 0; i < 10; ++i) dst[i] = 0;
    EXPECT_STREQ("", StdFun::strncpy(dst, "", 0));
    for (int i = 0; i < 10; ++i) dst[i] = 0;
    EXPECT_STREQ("", StdFun::strncpy(dst, "", 1));
}


/*********************************************************************************************/
/*********************************************************************************************/
int StdFun::strcmp(const char *s1, const char *s2) {
    assert(s1 != nullptr && s2 != nullptr);
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2; // 必须放在循环体内，否则会出错
    }
    // 需要先转换为unsigned char类型之后才进行减运算
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

TEST(StdFun, strcmp) {
    EXPECT_EQ(0, StdFun::strcmp("", ""));
    EXPECT_EQ(0, StdFun::strcmp("a", "a"));
    EXPECT_EQ(0, StdFun::strcmp("abbbbb", "abbbbb"));
    EXPECT_EQ(5, StdFun::strcmp("6", "1"));
    EXPECT_EQ(5, StdFun::strcmp("1234567", "1234562"));
    EXPECT_EQ(-5, StdFun::strcmp("1", "6"));
    EXPECT_EQ(-5, StdFun::strcmp("1234562", "1234567"));
}


/*********************************************************************************************/
/*********************************************************************************************/
int StdFun::strncmp(const char *s1, const char *s2, size_t n) {
    assert(s1 != nullptr && s2 != nullptr);
    while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2;
        --n;
    }
    // 注意n = 0的时候应该横返回0, 而且必须放在while的后边
    if (n == 0) return 0;
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

TEST(StdFun, strncmp) {
    EXPECT_EQ(0, StdFun::strncmp("", "", 0));
    EXPECT_EQ(0, StdFun::strncmp("", "1", 0));
    EXPECT_EQ(0, StdFun::strncmp("a", "a", 1));
    EXPECT_EQ(0, StdFun::strncmp("a", "a", 2));
    EXPECT_EQ(0, StdFun::strncmp("abbbbb", "abbbbb", 20));
    EXPECT_EQ(0, StdFun::strncmp("abbbbb", "abbbbb", 5));
    EXPECT_EQ(5, StdFun::strncmp("6", "1", 1));
    EXPECT_EQ(-5, StdFun::strncmp("1", "6", 1));
    EXPECT_EQ(5, StdFun::strncmp("1234567", "1234562", 10));
    EXPECT_EQ(-5, StdFun::strncmp("1234562", "1234567", 10));
    EXPECT_EQ(0, StdFun::strncmp("1234567", "1234562", 6));
}


/*********************************************************************************************/
/*********************************************************************************************/
char* StdFun::strcat(char *dst, const char *src) {
    assert(dst != nullptr && src != nullptr);
    char *tmp = dst;
    while (*dst != '\0') {
        ++dst;
    }
    while ((*dst++ = *src++) != '\0');
    return tmp;
}

TEST(StdFun, strcat) {
    char dst[10] = "1234";
    EXPECT_STREQ("1234", StdFun::strcat(dst, ""));
    EXPECT_STREQ("123456", StdFun::strcat(dst, "56"));
    EXPECT_STREQ("123456789", StdFun::strcat(dst, "789"));
}


/*********************************************************************************************/
/*********************************************************************************************/
// 注意声明中ch为int型的
char* StdFun::strchr(const char *str, int ch) {
    assert(str != nullptr);

    while (*str != '\0' && *str != ch) {
        ++str;
    }
    return (*str == '\0') ? nullptr :(char *)str;
}

TEST(StdFun, strchr) {
    EXPECT_TRUE(nullptr == StdFun::strchr("", 0));
    EXPECT_TRUE(nullptr == StdFun::strchr("123456789", 0));
    EXPECT_TRUE(nullptr == StdFun::strchr("123456789", 'a'));
    EXPECT_EQ('1', *StdFun::strchr("123456789", '1'));
    EXPECT_EQ('2', *StdFun::strchr("123456789", '2'));
    EXPECT_EQ('8', *StdFun::strchr("123456789", '8'));
    EXPECT_EQ('9', *StdFun::strchr("123456789", '9'));
}


/*********************************************************************************************/
/*********************************************************************************************/
char* StdFun::strstr(const char *str1, const char *str2) {
    assert(str1 != nullptr && str2 != nullptr);

    // 需要注意str2为“”和str1为“”的情况
    if (str2[0] == '\0') return (char *)str1;

    int n = 0;
    while (*str1 != '\0') {
        for (n = 0; *(str1 + n) == *(str2 + n); ++n) {
            if (*(str2 +n + 1) == '\0') {
                return (char *)str1;
            }
        }
        ++str1;
    }
    return nullptr;
}

TEST(StdFun, strstr) {
    EXPECT_EQ('\0', *StdFun::strstr("", ""));
    EXPECT_EQ('1', *StdFun::strstr("1", ""));
    EXPECT_EQ('1', *StdFun::strstr("123456", "12"));
    EXPECT_EQ('4', *StdFun::strstr("123456", "456"));
    EXPECT_EQ('6', *StdFun::strstr("123456", "6"));
}

/*********************************************************************************************/
/*********************************************************************************************/
int StdFun::memcmp(const void *s1, const void *s2, size_t n) {
    assert(s1 != nullptr && s2 != nullptr);
    const unsigned char *_s1 = (unsigned char *)s1;
    const unsigned char *_s2 = (unsigned char *)s2;
    while (n > 0 && *_s1 == *_s2) {
        ++_s1;
        ++_s2;
        --n;
    }
    if (n == 0) return 0;
    return (*_s1 - *_s2);
}

TEST(StdFun, memcmp) {
    EXPECT_EQ(0, StdFun::memcmp("", "", 0));
    EXPECT_EQ(0, StdFun::memcmp("", "1", 0));
    EXPECT_EQ(0, StdFun::memcmp("a", "a", 1));
    EXPECT_EQ(0, StdFun::memcmp("a", "a", 2));
    EXPECT_EQ(0, StdFun::memcmp("abbbbb", "abbbbb", 20));
    EXPECT_EQ(0, StdFun::memcmp("abbbbb", "abbbbb", 5));
    EXPECT_EQ(5, StdFun::memcmp("6", "1", 1));
    EXPECT_EQ(-5, StdFun::memcmp("1", "6", 1));
    EXPECT_EQ(5, StdFun::memcmp("1234567", "1234562", 10));
    EXPECT_EQ(-5, StdFun::memcmp("1234562", "1234567", 10));
    EXPECT_EQ(0, StdFun::memcmp("1234567", "1234562", 6));
}

/*********************************************************************************************/
/*********************************************************************************************/
void* StdFun::memset(void *s, int c, size_t n) {
    assert(s != nullptr);
    unsigned char *ptr = (unsigned char *)s;
    while (n-- > 0) {
        *ptr++ = (unsigned char)c;
    }

    return (s);
}

/*********************************************************************************************/
/*********************************************************************************************/
void* StdFun::memcpy(void *dst, const void *src, size_t n) {
    assert(dst != nullptr && src != nullptr);
    unsigned char *_dst = (unsigned char *)dst;
    const unsigned char *_src = (unsigned char *)src;
    while (n-- > 0) {
        *_dst++ = *_src++;
    }
    return (dst);
}

/*********************************************************************************************/
/*********************************************************************************************/
void* StdFun::memmove(void *dst, const void *src, size_t n) {
    assert(dst != nullptr && src != nullptr);
    unsigned char *_dst = (unsigned char *)dst;
    const unsigned char *_src = (unsigned char *)src;
    if (dst < src){
        while (n-- > 0) {
            *_dst++ = *_src++;
        }
    } else if (dst > src) {
        _dst += n;
        _src += n;
        while (n-- > 0) {
            *(--_dst) = *(--_src);
        }
    }
    return (dst);
}

/*********************************************************************************************/
/*********************************************************************************************/
void* StdFun::memchr(const void* src, int c, size_t n) {
    assert(src != nullptr);
    const unsigned char *_src = (unsigned char *)src;
    if (n > 0 && *_src != (unsigned char)c) {
        --n;
        ++_src;
    }
    return (void *)(n == 0 ? nullptr : _src);
}

/*********************************************************************************************/
/*********************************************************************************************/
void StdFun::itoa(int i, char *a) {
    assert(a != nullptr);
    char *p = a;
    if (i < 0) {
        *p++ = '-';
        i = 0 - i;
    }

    int tmp = 1;
    while (i / tmp / 10 != 0) {
        tmp *= 10;
    }

    while (tmp != 0) {
        *p++ = i / tmp + '0';
        i %= tmp;
        tmp /= 10;
    }
    *p = '\0';
}

TEST(StdFun, itoa) {
    char a[100];

    StdFun::itoa(0, a);
    EXPECT_STREQ("0", a);
    StdFun::itoa(5, a);
    EXPECT_STREQ("5", a);
    StdFun::itoa(123456, a);
    EXPECT_STREQ("123456", a);
    StdFun::itoa(-123456, a);
    EXPECT_STREQ("-123456", a);
    StdFun::itoa((int)0x7fffffff, a);
    EXPECT_STREQ("2147483647", a);
    StdFun::itoa((int)0x80000001, a);
    EXPECT_STREQ("-2147483647", a);
}

/*********************************************************************************************/
/*********************************************************************************************/
int StdFun::atoi(char *a) {
    bool isNegative = false;
    int result = 0;
    while (*a == ' ' || *a == '\t') {
        ++a;
    }

    if (*a == '-' || *a == '+') {
        isNegative = (*a++ == '-');
    }

    while (*a <= '9' && *a >= '0') {
        result *= 10;
        result += (*a++ - '0');
    }

    return (isNegative ? (0 - result) : result);
}

TEST(StdFun, atoi) {
    EXPECT_EQ(0, StdFun::atoi("0"));
    EXPECT_EQ(5, StdFun::atoi("5"));
    EXPECT_EQ(12345, StdFun::atoi("12345"));
    EXPECT_EQ(-12345, StdFun::atoi("-12345"));
    EXPECT_EQ(12345, StdFun::atoi("  12345"));
    EXPECT_EQ(-12345, StdFun::atoi("  -12345"));
    EXPECT_EQ((int)0x7fffffff, StdFun::atoi("2147483647"));
    EXPECT_EQ((int)0x80000001, StdFun::atoi("-2147483647"));
}
