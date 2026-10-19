#pragma once
#include <vector>

// намираме минималния елемент във v[from ... to-1]
template <class T>
size_t findMinIndex(std::vector<T>& v, size_t from, size_t to){
  size_t minIndex = from;
  for(size_t i = from + 1; i < to; i++){
    if(v[minIndex] > v[i]){
      minIndex = i;
    }
  }
  return minIndex;
}

// сложност по време: О(n)
// сложност по памет: О(1)

template <class T>
void selectionSort(std::vector<T>& v){
  for(size_t i = 0; i < v.size(); i++){
    size_t min = findMinIndex(v, i, v.size());
    std::swap(v[i], v[min]);
  }
}

// сложност по време: O(n^2)
// сложност по памет: O(1)