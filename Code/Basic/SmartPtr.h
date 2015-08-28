//
// Created by ruan on 15-7-29.
//

#ifndef LEARN_SMARTPTR_H
#define LEARN_SMARTPTR_H
template <typename T>
class SmartPtr {
private:
    T *_ptr;
    size_t *_count;

public:
    SmartPtr(T *p = nullptr);

    SmartPtr(const SmartPtr &src);

    SmartPtr& operator=(const SmartPtr &rhs);

    T& operator*();

    T* operator->();

    ~SmartPtr();
};
#endif //LEARN_SMARTPTR_H
