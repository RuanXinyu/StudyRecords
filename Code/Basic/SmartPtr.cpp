//
// Created by ruan on 15-7-29.
//

#include <stddef.h>
#include <gtest/gtest.h>
#include "SmartPtr.h"

template <typename T>
SmartPtr<T>::SmartPtr(T *p): _ptr(p), _count(new size_t) {
    *_count = (p == nullptr) ? 0 : 1;
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr &src): _ptr(src._ptr), _count(src._count) {
    if (&src != this) {
        ++(*_count);
    }
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr &rhs){
    if (&rhs != this) {
        if (_ptr != nullptr && (--(*_count)) == 0) {
            delete _ptr;
            delete _count;
        } else {
            _count = rhs._count;
            _ptr = rhs._ptr;
            ++(*_count);
        }
    }
    return *this;
}

template <typename T>
T& SmartPtr<T>::operator*() {
    if (_ptr != nullptr) {
        return *_ptr;
    }
    throw "nullptr";
}

template <typename T>
T* SmartPtr<T>::operator->() {
    if (_ptr != nullptr) {
        return _ptr;
    }
    throw "nullptr";
}

template <typename T>
SmartPtr<T>::~SmartPtr() {
    if ((--(*_count)) == 0) {
        delete _ptr;
        delete _count;
    }
}

TEST(SmartPtr, SmartPtr) {
    SmartPtr<char> cp1(new char('a'));
    SmartPtr<char> cp2(cp1);
    SmartPtr<char> cp3;
    cp3 = cp2;
    cp3 = cp1;
    cp3 = cp3;
    SmartPtr<char> cp4(new char('b'));
    cp3 = cp4;
}