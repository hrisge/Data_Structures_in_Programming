#include <iostream>
#include <stdexcept>
#include "LinkedList.hpp"
#include "DetectCycle.hpp"
#include "ValidParentheses.hpp"
#include "EvaluateRPN.hpp"

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

    std::cout << std::boolalpha << detectCycle(head) << std::endl; // true

    std::cout << std::boolalpha << validParentheses("(abc)[def]{ghi}") << std::endl; // true
    std::cout << std::boolalpha << validParentheses("") << std::endl; // true
    std::cout << std::boolalpha << validParentheses("[(])") << std::endl; // false
    std::cout << std::boolalpha << validParentheses("(()") << std::endl; // false
    std::cout << std::boolalpha << validParentheses("())") << std::endl; // false
    std::cout << std::boolalpha << validParentheses("([{}])") << std::endl; // true

    std::cout << evaluateRPN({"2","1","+","3","*"}) << std::endl;
    std::cout << evaluateRPN({"4","13","5","/","+"}) << std::endl;
    try{
        evaluateRPN({"1", "2"});
    }
    catch(std::invalid_argument e){
        std::cout << e.what() << std::endl;
    }
    try{
        evaluateRPN({"2", "+", "1"});
    }
    catch(std::invalid_argument e){
        std::cout << e.what() << std::endl;
    }
}