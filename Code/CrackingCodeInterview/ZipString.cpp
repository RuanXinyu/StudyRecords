//
// Created by ruan on 15-8-3.
//

#include <gtest/gtest.h>
#include "iostream"

using namespace std;

class Zipper {
public:
    static string zipString(string iniString) {
        if (iniString.size() == 0) return "";

        stringstream str;
        char cur = iniString[0];
        int count = 1;
        for (int i = 1; i < iniString.size(); ++i) {
            if (cur == iniString[i]) {
                ++count;
            } else {
                str << cur;
                str << count;
                cur = iniString[i];
                count = 1;
            }
        }
        str << cur;
        str << count;

        string result;
        str >> result;

        return (result.size() < iniString.size() ? result : iniString);
    }
};

TEST(CrackingCodeInterview, zipString) {
    string text("jjjjjjxxxxxxxooZLLLLLLLLQQQQQQQQQLLLLLLLLECXXXXXXXIIIIIIIIIhjjyyySSooooooooommmuuEEEEEEEEEnnnnnnnffffffAAAAAllllllllbbbbkkkkkkkkkkkkKKKKKKhhhhhhhhhooooooooooYCCCCCCOOOOOOOOOMMMMMMMMMMiiiiiivvvvvvvWWWWkkkkkkwwwwwwwMmmmmmmmmLLLwwwwwwwkkkjjjjjjttttQQQQQQQQQaaaaaaaFFFFFFFlllllllllggggggggggPPPPPPuuuuuuuuaYYYYYYwQQQFFFFFFFFFFaaaaapXXXXXXXxxxxxxQQQQQQQQQsssssGGGGfffffffddddddpppQQQQQQHHHTTTaaaaaaGGGGGGddyyyyyMhhllllllllllNNNNNNNNUUUWWWWWWLLLLLLLLLYYYYYYYYYYTTKKKKKKKKiiiiiiitttttttXXXXXXXXXLLLHZZZZZZZssssjjJJJEEEEEOOOOOttttttttttBBttttttTTTTTTTTTTrrrrttttRRRRRyyooooooaaaaaaaaarrrrrrrPPPPPPPjjPPPPddddddddddHHHHnnnnnnnnnnSSSSSSSSSSzzHHHHHHHHHddddddDDDzzzhhhhhfffffffffftttttteeeeeeeeEEEEEEEEEaaaaaaccccccccccFFFFFFFF");
    string result("j6x7o2Z1L8Q9L8E1C1X7I9h1j2y3S2o9m3u2E9n7f6A5l8b4k12K6h9o10Y1C6O9M10i6v7W4k6w7M1m8L3w7k3j6t4Q9a7F7l9g10P6u8a1Y6w1Q3F10a5p1X7x6Q9s5G4f7d6p3Q6H3T3a6G6d2y5M1h2l10N8U3W6L9Y10T2K8i7t7X9L3H1Z7s4j2J3E5O5t10B2t6T10r4t4R5y2o6a9r7P7j2P4d10H4n10S10z2H9d6D3z3h5f10t6e8E9a6c10F8");
    cout << Zipper::zipString(text) << endl;
    EXPECT_TRUE(result == Zipper::zipString(text));
    string a("");
    cout << a.size() << a.length() << endl;
}

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* partition(ListNode* pHead, int x) {
    if (pHead == nullptr || pHead->next == nullptr) return pHead;

    ListNode *head = pHead, *tmp;
    while (pHead->next != nullptr) {
        if (pHead->next->val < x) {
            tmp = pHead->next;
            pHead->next = pHead->next->next;
            tmp->next = head;
            head = tmp;
        } else {
            pHead = pHead->next;
        }
    }
    return head;
}

TEST(partition, partition) {
    int d;
    ListNode a(6), b(2), c(8);
    a.next = &b;
    b.next = &c;
    c.next = nullptr;
    ListNode *result = partition(&a, 9);
    cout << result->val << result->next->val << result->next->next->val << endl;
}
