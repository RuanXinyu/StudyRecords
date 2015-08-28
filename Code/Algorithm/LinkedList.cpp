//
// Created by ruan on 15-7-17.
//

#include <gtest/gtest.h>
#include "LinkedList.h"

void LinkedList::list_init(Node nodeList[], int count, int baseVal) {
    for (int i = 0; i < count - 1; ++i) {
        nodeList[i].value = baseVal + i;
        nodeList[i].next = &nodeList[i + 1];
    }
    nodeList[count - 1].value = baseVal + count - 1;
    nodeList[count - 1].next = nullptr;
}

void LinkedList::looplist_init(Node nodeList[], int count, int loopNodeIndex, int baseVal) {
    for (int i = 0; i < count - 1; ++i) {
        nodeList[i].value = baseVal + i;
        nodeList[i].next = &nodeList[i + 1];
    }
    nodeList[count - 1].value = baseVal + count - 1;
    nodeList[count - 1].next = &nodeList[loopNodeIndex];
}

string LinkedList::tostring(Node *head) {
    Node *tmp = head;
    stringstream text;
    while (tmp != nullptr) {
        text << tmp->value << " ";
        tmp = tmp->next;
    }
    return text.str();
}

string LinkedList::sequence_string(int start, int end, int step) {
    stringstream text;
    if(start <= end) {
        for (int i = start; i <= end; i += step) {
            text <<  i << " ";
        }
    } else {
        for (int i = start; i >= end; i -= step) {
            text << i << " ";
        }
    }
    return text.str();
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::find_middle_node(Node *head) {
    Node *fast = head, *slow = head;
    if (head == nullptr) {
        return nullptr;
    }

    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

TEST(LinkedList, List_FindMiddleNode) {
    EXPECT_TRUE(nullptr == LinkedList::find_middle_node(nullptr));

    Node nodeList[10];
    LinkedList::list_init(nodeList, 1);
    EXPECT_EQ(0, LinkedList::find_middle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 2);
    EXPECT_EQ(0, LinkedList::find_middle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 3);
    EXPECT_EQ(1, LinkedList::find_middle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    EXPECT_EQ(4, LinkedList::find_middle_node(nodeList)->value);
}


/*********************************************************************************************/
/*********************************************************************************************/
bool LinkedList::is_exist_loop(Node *head) {
    Node *fast = head, *slow = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) {
            return true;
        }
    }
    return false;
}

TEST(LinkedList, List_DetectListExsitLoop) {
    EXPECT_FALSE(LinkedList::is_exist_loop(nullptr));

    Node nodeList[10];
    LinkedList::list_init(nodeList, 1);
    EXPECT_FALSE(LinkedList::is_exist_loop(nodeList));
    LinkedList::list_init(nodeList, 2);
    EXPECT_FALSE(LinkedList::is_exist_loop(nodeList));
    LinkedList::list_init(nodeList, 3);
    EXPECT_FALSE(LinkedList::is_exist_loop(nodeList));
    LinkedList::list_init(nodeList, 10);
    EXPECT_FALSE(LinkedList::is_exist_loop(nodeList));

    LinkedList::looplist_init(nodeList, 1, 0);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
    LinkedList::looplist_init(nodeList, 2, 0);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
    LinkedList::looplist_init(nodeList, 3, 0);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
    LinkedList::looplist_init(nodeList, 10, 5);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
    LinkedList::looplist_init(nodeList, 10, 8);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
    LinkedList::looplist_init(nodeList, 10, 9);
    EXPECT_TRUE(LinkedList::is_exist_loop(nodeList));
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::reverse_loop(Node *head) {
    Node *current, *tmp;
    if (head == nullptr  || head->next == nullptr) {
        return head;
    }

    current = head->next;
    head->next = nullptr;
    while (current != nullptr) {
        tmp = current;
        current = current->next;
        tmp->next = head;
        head = tmp;
    }
    return head;
}

TEST(LinkedList, List_ReverseList_Loop) {
    EXPECT_TRUE(nullptr == LinkedList::reverse_loop(nullptr));

    Node nodeList[10];
    string resultListString = "";

    LinkedList::list_init(nodeList, 1);
    resultListString = LinkedList::tostring(LinkedList::reverse_loop(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(0, 0, 1) == resultListString);
    LinkedList::list_init(nodeList, 2);
    resultListString = LinkedList::tostring(LinkedList::reverse_loop(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(1, 0, 1) == resultListString);
    LinkedList::list_init(nodeList, 10);
    resultListString = LinkedList::tostring(LinkedList::reverse_loop(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(9, 0, 1) == resultListString);
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::reverse_recursion(Node *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node *newHead = reverse_recursion(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

TEST(LinkedList, List_ReverseList_Recursion) {
    EXPECT_TRUE(nullptr == LinkedList::reverse_recursion(nullptr));

    Node nodeList[10];
    string resultListString = "";

    LinkedList::list_init(nodeList, 1);
    resultListString = LinkedList::tostring(LinkedList::reverse_recursion(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(0, 0, 1) == resultListString);
    LinkedList::list_init(nodeList, 2);
    resultListString = LinkedList::tostring(LinkedList::reverse_recursion(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(1, 0, 1) == resultListString);
    LinkedList::list_init(nodeList, 10);
    resultListString = LinkedList::tostring(LinkedList::reverse_recursion(nodeList));
    EXPECT_TRUE(LinkedList::sequence_string(9, 0, 1) == resultListString);
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::find_node_by_index_from_behind(Node *head, int index) {
    Node *ahead = head, *behind = head;
    if (index <= 0 || head == nullptr) {
        return nullptr;
    }

    while (index-- > 1 && ahead != nullptr) {
        ahead = ahead->next;
    }

    if (index > 1) return nullptr;

    while (ahead->next != nullptr) {
        ahead = ahead->next;
        behind = behind->next;
    }
    return behind;
}

TEST(LinkedList, List_FindNodeByIndexFromBehind) {
    Node nodeList[10];

    EXPECT_TRUE(nullptr == LinkedList::find_node_by_index_from_behind(nullptr, 5));

    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE(nullptr == LinkedList::find_node_by_index_from_behind(nodeList, 0));
    EXPECT_TRUE(nullptr == LinkedList::find_node_by_index_from_behind(nodeList, 20));
    EXPECT_TRUE(9 == LinkedList::find_node_by_index_from_behind(nodeList, 1)->value);
    EXPECT_TRUE(5 == LinkedList::find_node_by_index_from_behind(nodeList, 5)->value);
    EXPECT_TRUE(0 == LinkedList::find_node_by_index_from_behind(nodeList, 10)->value);
}


/*********************************************************************************************/
/*********************************************************************************************/
void LinkedList::print_from_behind_recursion(Node *head, stringstream &result) {
    if (head == nullptr) {
        return;
    }
    print_from_behind_recursion(head->next, result);
    result << head->value << " ";
}

TEST(LinkedList, List_PrintListFromBehind_Recursion) {
    Node nodeList[10];
    stringstream text, &result = text;

    result.str("");
    LinkedList::print_from_behind_recursion(nullptr, result);
    EXPECT_TRUE("" == result.str());

    result.str("");
    LinkedList::list_init(nodeList, 1);
    LinkedList::print_from_behind_recursion(nodeList, result);
    EXPECT_TRUE("0 " == result.str());

    result.str("");
    LinkedList::list_init(nodeList, 10);
    LinkedList::print_from_behind_recursion(nodeList, result);
    EXPECT_TRUE("9 8 7 6 5 4 3 2 1 0 " == result.str()) << result.str();
}


/*********************************************************************************************/
/*********************************************************************************************/
string LinkedList::print_from_behind_loop(Node *head) {
    if (head == nullptr) {
        return "";
    }

    stack<Node *> s;
    stringstream result;
    while (head != nullptr) {
        s.push(head);
        head = head->next;
    }

    while (!s.empty()) {
        result << s.top()->value << " ";
        s.pop();
    }
    return result.str();
}

TEST(LinkedList, List_PrintListFromBehind_Loop) {
    Node nodeList[10];

    EXPECT_TRUE("" == LinkedList::print_from_behind_loop(nullptr));

    LinkedList::list_init(nodeList, 1);
    EXPECT_TRUE("0 " == LinkedList::print_from_behind_loop(nodeList));

    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE("9 8 7 6 5 4 3 2 1 0 " == LinkedList::print_from_behind_loop(nodeList));
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::merge_sorted_list_loop(Node *head1, Node *head2) {
    if (head1 == nullptr) return head2;
    if (head2 == nullptr) return head1;

    Node *newHead = nullptr;
    if (head1->value < head2->value) {
        newHead = head1;
        head1 = head1->next;
    } else {
        newHead = head2;
        head2 = head2->next;
    }

    Node *tmp = newHead;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->value < head2->value) {
            tmp->next = head1;
            head1 = head1->next;
        } else {
            tmp->next = head2;
            head2 = head2->next;
        }
        tmp = tmp->next;
    }

    if (head1 == nullptr) tmp->next = head2;
    if (head2 == nullptr) tmp->next = head1;

    return newHead;
}

TEST(LinkedList, List_MergeSortedList_Loop) {
    Node nodeList1[10], nodeList2[10];

    LinkedList::list_init(nodeList1, 5);
    EXPECT_TRUE(nullptr == LinkedList::merge_sorted_list_loop(nullptr, nullptr));
    EXPECT_TRUE("0 1 2 3 4 " == LinkedList::tostring(LinkedList::merge_sorted_list_loop(nullptr, nodeList1)));
    EXPECT_TRUE("0 1 2 3 4 " == LinkedList::tostring(LinkedList::merge_sorted_list_loop(nodeList1, nullptr)));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 3);
    EXPECT_TRUE("0 1 2 3 3 4 4 5 6 7 " == LinkedList::tostring(LinkedList::merge_sorted_list_loop(nodeList1, nodeList2)));

    LinkedList::list_init(nodeList1, 5, 3);
    LinkedList::list_init(nodeList2, 5);
    EXPECT_TRUE("0 1 2 3 3 4 4 5 6 7 " == LinkedList::tostring(LinkedList::merge_sorted_list_loop(nodeList1, nodeList2)));
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::merge_sorted_list_recursion(Node *head1, Node *head2) {
    if (head1 == nullptr) return head2;
    if (head2 == nullptr) return head1;

    Node *tmp = nullptr;
    if (head1->value < head2->value) {
        tmp = head1;
        tmp->next = merge_sorted_list_recursion(head1->next, head2);
    } else {
        tmp = head2;
        tmp->next = merge_sorted_list_recursion(head1, head2->next);
    }
    return tmp;
}

TEST(LinkedList, List_MergeSortedList_Recursion) {
    Node nodeList1[10], nodeList2[10];

    LinkedList::list_init(nodeList1, 5);
    EXPECT_TRUE(nullptr == LinkedList::merge_sorted_list_recursion(nullptr, nullptr));
    EXPECT_TRUE("0 1 2 3 4 " == LinkedList::tostring(LinkedList::merge_sorted_list_recursion(nullptr, nodeList1)));
    EXPECT_TRUE("0 1 2 3 4 " == LinkedList::tostring(LinkedList::merge_sorted_list_recursion(nodeList1, nullptr)));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 3);
    EXPECT_TRUE("0 1 2 3 3 4 4 5 6 7 " == LinkedList::tostring(LinkedList::merge_sorted_list_recursion(nodeList1, nodeList2)));

    LinkedList::list_init(nodeList1, 5, 3);
    LinkedList::list_init(nodeList2, 5);
    EXPECT_TRUE("0 1 2 3 3 4 4 5 6 7 " == LinkedList::tostring(LinkedList::merge_sorted_list_recursion(nodeList1, nodeList2)));
}

/*********************************************************************************************/
/*********************************************************************************************/
bool LinkedList::is_intersected(Node *head1, Node *head2) {
    if(head1 == nullptr || head2 == nullptr) return false;

    while (head1->next != nullptr) {
        head1 = head1->next;
    }

    while (head2->next != nullptr) {
        head2 = head2->next;
    }

    return (head1 == head2);
}

TEST(LinkedList, List_IsIntersected) {
    Node nodeList1[10], nodeList2[10];

    EXPECT_FALSE(LinkedList::is_intersected(nullptr, nullptr));
    EXPECT_FALSE(LinkedList::is_intersected(nullptr, nodeList1));
    EXPECT_FALSE(LinkedList::is_intersected(nodeList1, nullptr));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 10);
    nodeList2[4].next = &nodeList1[2];
    EXPECT_TRUE(LinkedList::is_intersected(nodeList1, nodeList2));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 10);
    EXPECT_FALSE(LinkedList::is_intersected(nodeList1, nodeList2));
}

/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::find_first_intersected_node(Node *head1, Node *head2) {
    if(head1 == nullptr || head2 == nullptr) return nullptr;

    int len1 = 1, len2 = 1;
    Node *tmp1 = head1;
    while (tmp1->next != nullptr) {
        tmp1 = tmp1->next;
        ++len1;
    }

    Node *tmp2 = head2;
    while (tmp2->next != nullptr) {
        tmp2 = tmp2->next;
        ++len2;
    }
    if (tmp1 != tmp2) return nullptr;

    while(len1 > len2) {
        head1 = head1->next;
        --len1;
    }

    while(len2 > len1) {
        head2 = head2->next;
        --len2;
    }

    while (head1 != head2) {
        head1 = head1->next;
        head2 = head2->next;
    }

    return head1;
}

TEST(LinkedList, find_first_intersected_node) {
    Node nodeList1[10], nodeList2[10];

    EXPECT_TRUE(nullptr == LinkedList::find_first_intersected_node(nullptr, nullptr));
    EXPECT_TRUE(nullptr == LinkedList::find_first_intersected_node(nullptr, nodeList1));
    EXPECT_TRUE(nullptr == LinkedList::find_first_intersected_node(nodeList1, nullptr));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 10);
    EXPECT_TRUE(nullptr == LinkedList::find_first_intersected_node(nodeList1, nodeList2));

    LinkedList::list_init(nodeList1, 5);
    LinkedList::list_init(nodeList2, 5, 10);
    nodeList2[4].next = &nodeList1[2];
    EXPECT_TRUE(2 == LinkedList::find_first_intersected_node(nodeList1, nodeList2)->value);

}


/*********************************************************************************************/
/*********************************************************************************************/

Node* LinkedList::find_first_circle_node(Node *head) {
    Node *fast = head, *slow = head, *seperateNode = nullptr, *tmp = nullptr;
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            seperateNode = fast;
            break;
        }
    }

    if (seperateNode == nullptr) return nullptr;

    int len1 = 1, len2 =1;
    tmp = head;
    while (tmp->next != seperateNode) {
        tmp = tmp->next;
        ++len1;
    }
    tmp = seperateNode;
    while (tmp->next != seperateNode) {
        tmp = tmp->next;
        ++len2;
    }

    while (len1 > len2) {
        head = head->next;
        --len1;
    }
    while (len2 > len1) {
        seperateNode = seperateNode->next;
        --len1;
    }

    while (seperateNode != head) {
        seperateNode = seperateNode->next;
        head = head->next;
    }
    return head;
}

TEST(LinkedList, find_first_circle_node) {
    EXPECT_TRUE(nullptr == LinkedList::find_first_circle_node(nullptr));

    Node nodeList[10];
    LinkedList::list_init(nodeList, 1);
    EXPECT_TRUE(nullptr == LinkedList::find_first_circle_node(nodeList));
    LinkedList::list_init(nodeList, 2);
    EXPECT_TRUE(nullptr == LinkedList::find_first_circle_node(nodeList));
    LinkedList::list_init(nodeList, 3);
    EXPECT_TRUE(nullptr == LinkedList::find_first_circle_node(nodeList));
    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE(nullptr == LinkedList::find_first_circle_node(nodeList));

    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[0];
    EXPECT_TRUE(0 == LinkedList::find_first_circle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[1];
    EXPECT_TRUE(1 == LinkedList::find_first_circle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[2];
    EXPECT_TRUE(2 == LinkedList::find_first_circle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[5];
    EXPECT_TRUE(5 == LinkedList::find_first_circle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[8];
    EXPECT_TRUE(8 == LinkedList::find_first_circle_node(nodeList)->value);
    LinkedList::list_init(nodeList, 10);
    nodeList[9].next = &nodeList[9];
    EXPECT_TRUE(9 == LinkedList::find_first_circle_node(nodeList)->value);
}


/*********************************************************************************************/
/*********************************************************************************************/
Node* LinkedList::delete_node(Node *head, Node *toBeDeleted) {
    if (head == nullptr || toBeDeleted == nullptr) {
        return head;
    }

    Node *tmp = head;
    if (toBeDeleted->next == nullptr) {
        if (tmp == toBeDeleted) {
//            delete tmp;
            return nullptr;
        }
        while (tmp->next != toBeDeleted) {
            tmp = tmp->next;
        }
        if(tmp->next == toBeDeleted) {
//            delete tmp->next;
            tmp->next = nullptr;
        }
    } else {
        tmp = toBeDeleted->next;
        toBeDeleted->value = tmp->value;
        toBeDeleted->next = tmp->next;
//        delete tmp;
    }
    return head;
}

TEST(LinkedList, delete_node) {
    Node nodeList[10];

    EXPECT_TRUE(nullptr == LinkedList::delete_node(nullptr, nullptr));
    EXPECT_TRUE(nullptr == LinkedList::delete_node(nullptr, nodeList));

    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE("0 1 2 3 4 5 6 7 8 9 " == LinkedList::tostring(LinkedList::delete_node(nodeList, nullptr)));
    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE("1 2 3 4 5 6 7 8 9 " == LinkedList::tostring(LinkedList::delete_node(nodeList, &nodeList[0])));
    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE("0 1 2 3 4 6 7 8 9 " == LinkedList::tostring(LinkedList::delete_node(nodeList, &nodeList[5])));
    LinkedList::list_init(nodeList, 10);
    EXPECT_TRUE("0 1 2 3 4 5 6 7 8 " == LinkedList::tostring(LinkedList::delete_node(nodeList, &nodeList[9])));

    LinkedList::list_init(nodeList, 1);
    EXPECT_TRUE(nullptr == LinkedList::delete_node(nodeList, &nodeList[0]));
}

