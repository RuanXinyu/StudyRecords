//
// Created by ruan on 15-7-22.
//

#ifndef LEARN_STDFUN_H
#define LEARN_STDFUN_H

class StdFun {
public:
    static size_t strlen(const char *s);

    static char * strcpy(char *s1, const char *s2);

    static char *strncpy(char *s1, const char *s2, size_t n);

    static int strcmp(const char *s1, const char *s2);

    static int strncmp(const char *s1, const char *s2, size_t n);

    static char *strcat(char *dst, const char *src);

    static char *strchr(const char *str, int ch);

    static char *strstr(const char *str1, const char *str2);

    static int memcmp(const void *s1, const void *s2, size_t n);

    static void *memset(void *s, int c, size_t n);

    static void *memcpy(void *dst, const void *src, size_t n);

    static void *memmove(void *dst, const void *src, size_t n);

    static void *memchr(const void* src, int c, size_t n);

    static void itoa(int i, char *a);

    static int atoi(char *a);
};
#endif //LEARN_STDFUN_H
