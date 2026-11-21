#pragma once

#include "LinkedList.hpp"
#include "Stack.hpp"
#include <functional>
template <class T, class R>
R foldr(const std::function<R(const T&, const T&)> op, const R& nv, const LinkedList<T>& list){
  Stack<R> s;
  R result = nv;
  for(const T& x : list){
    s.push(x);
  }
  while(!s.empty()){
    result = op(s.peek(), result);
    s.pop();
  }
  return result;
}