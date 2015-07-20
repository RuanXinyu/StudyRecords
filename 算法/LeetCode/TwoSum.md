1. Two Sum
===
### 问题描述
> Given an array of integers, find two numbers such that they add up to a specific target number.

> The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

> You may assume that each input would have exactly one solution.

> **Input**: `numbers={2, 7, 11, 15}, target=9`
> **Output**: `index1=1, index2=2`


### 解决方案
+ 暴力型遍历，当然也是最次的，leetcode上显示超时
```cpp
int* twoSum(int* nums, int numsSize, int target) {
    int *result = (int *)malloc(2 * sizeof(int));
    int i, j;
    for (i = 0; i < numsSize -1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if(nums[i] + nums[j] == target) {
                result[0] = nums[i];
                result[1] = nums[j];
                return result;
            }
        }
    }
    return NULL;
}
```

+ 通过map实现，复杂度为Nlog（N），因为红黑树时NLog(N)的
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    map<int, int> hmap;
    for (int i = 0; i < nums.size(); i++) {
        if (hmap.count(target - nums[i])) {
            result.push_back(hmap[target - nums[i]] + 1);
            result.push_back(i + 1);
            return result;
        }
        if (!hmap.count(nums[i])) {
            hmap.insert(pair<int, int>(nums[i], i));
        }
    }
    return result;
}
```

### 扩展
> 如果数组为有序的，则不需要通过map实现，直接一边从头遍历，一边从尾部遍历即可。