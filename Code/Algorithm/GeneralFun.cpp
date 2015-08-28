//
// Created by ruan on 15-8-14.
//

#include "GeneralFun.h"

// 最大公约数
long long gcd(long long x, long long y) {
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}