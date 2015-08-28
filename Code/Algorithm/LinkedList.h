//
// Created by ruan on 15-7-17.
//

#ifndef LEARN_LINKEDLIST_H
#define LEARN_LINKEDLIST_H

#include "iostream"
#include "stack"
using namespace std;

typedef struct Node {
    int value;
    struct Node *next;
} Node;


class LinkedList {
public:
    static void list_init(Node nodeList[], int count, int baseVal = 0);
    static void looplist_init(Node nodeList[], int count, int loopNodeIndex, int baseVal = 0);
    static string tostring(Node *head);
    static string sequence_string(int start, int end, int step);

    static Node* find_middle_node(Node *head);

    static bool is_exist_loop(Node *head);

    static Node* reverse_loop(Node *head);
    static Node* reverse_recursion(Node *head);

    static Node* find_node_by_index_from_behind(Node *head, int index);

    static void print_from_behind_recursion(Node *head, stringstream &result);
    static string print_from_behind_loop(Node *head);

    static Node* merge_sorted_list_loop(Node *head1, Node *head2);
    static Node* merge_sorted_list_recursion(Node *head1, Node *head2);
    static bool  is_intersected(Node *head1, Node *head2);
    static Node* find_first_intersected_node(Node *head1, Node *head2);
    static Node* find_first_circle_node(Node *head);
    static Node* delete_node(Node *head, Node *toBeDeleted);

};

#endif //LEARN_LINKEDLIST_H
