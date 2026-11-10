#pragma once
#include <utility>

template <class IteratorType>
IteratorType minElement(IteratorType begin, IteratorType end){
  IteratorType min = begin;
  for(IteratorType j = begin; j != end; ++j){
    if(*j < *min) min = j;
  }
  return min;
}


template <class IteratorType>
void sort(IteratorType begin, IteratorType end){
  for(IteratorType i = begin; i != end; ++i){
    IteratorType min = minElement(i, end);
    std::swap(*i, *min);
  }
}

// в този вид sort може да се използва за всички структури, които използват итератор
// както и за обикновени масиви, например така:
/*
  T* arr = new T[n];
  sort(arr, arr + n);
*/
// това ще работи, понеже обикновения указател изпълнява всички условия,
// които сме поставили върху типа за итератор