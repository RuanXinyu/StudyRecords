//
// Created by ruan on 15-7-16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "NoClassification.h"

/********************************************************************************************************/
/*****************************************dividing line**************************************************/
/********************************************************************************************************/

bool Usage_Sizeof(const char str[]) {
    char text[20] = "This is text!";
    char *ptr = text;
    printf("sizeof(str):%d, sizeof(text):%d, sizeof(ptr):%d, strlen(text):%d, sizeof(double):%d, sizeof(float):%d\n", sizeof(str), sizeof(text), sizeof(ptr), strlen(text), sizeof(double), sizeof(float));
    return true;
}

void Usage_Variable(void) {
    char* a, b; // a is a pointer, b is not.
    printf("%d %d\n", a, b);
    printf("a is %s NULL\n", a == NULL ? "" : "not");
}

void GetMem(char **ptr) {
    *ptr = (char *)malloc(100);
}

void Usage_PtrTest() {
    char *str = NULL;
    GetMem(&str);
    strcpy(str, "this is a text");
    printf("%s\n", str);
    free(str);
}

class A { int a; virtual void fun(){};};
class B { int a; virtual void fun(){};};
class C: public A { int a, b, c; virtual void fun(){};};
class D: public A {int c,b,f;};
class E: virtual public D, virtual public C{int b,e,f;};

void Usage_VirtualClass() {
    printf("%d %d %d %d %d\n", sizeof(A), sizeof(B), sizeof(C), sizeof(D), sizeof(E));
}

TEST(NoClassification, Usage_VirtualClass) {
    Usage_VirtualClass();
}

void NoClassificationTest(void) {
    Usage_Sizeof("This is text!");
    Usage_Variable();
    Usage_PtrTest();
}