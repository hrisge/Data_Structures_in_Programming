#pragma once

#include "LinkedList.hpp"
template <class T>
class Stack {
  LinkedList<T> list;
public:

  bool empty() const {
    return list.empty();
  }

  size_t size() const {
    return list.size();
  }

  void push(const T& element) {
    list.push_front(element);
  }

  void pop(const T& element){
    list.pop_front();
  }

  T& peek() const {
    return *list.begin();
  }

};