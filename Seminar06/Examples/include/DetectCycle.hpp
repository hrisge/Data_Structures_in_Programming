#pragma once

struct Node{
    int data;
    Node* next;
    Node(int data, Node* next = nullptr) :
    data(data), next(next) {}
};

bool detectCycle(Node* head){
    if(!head && !head->next) return false;

    Node* slow = head;
    Node* fast = head->next;

    while(slow != fast && slow && fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow == fast;
}