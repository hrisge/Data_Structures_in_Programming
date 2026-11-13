#include <ios>
#include <iostream>
#include "LinkedList.hpp"

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

int main() {
    LinkedList<int> ll;

    for(int i = 10; i > 0; --i){
        ll.push_back(i);
    }

    ll.quickSort();

    for(int x : ll){
        std::cout << x << " ";
    }
    std::cout << std::endl;


    Node* head = new Node(1,
    new Node(5,
    new Node(3)));
    Node* iter;
    for(iter = head; iter->next != nullptr; iter = iter->next){}
    Node* cycleStart = new Node(10,
    new Node(12,
    new Node(13,
    new Node(4))));
    Node* iter2;
    for(iter2 = cycleStart; iter2->next != nullptr; iter2 = iter2->next){}
    iter2->next = cycleStart;
    iter->next = cycleStart;

    std::cout << std::boolalpha << detectCycle(head) << std::endl;
}
