#pragma once
#include <functional>
#include <vector>


// примера е с Bubble Sort
// може да се направи с кой да е алгоритъм за сортиране
template <class T>
void sortBy(std::vector<T>& v, const std::function<bool(const T&, const T&)>& lessThan){
  for(size_t i = 0; i < v.size(); i++){
    for(size_t j = 0; j < v.size() - i - 1; j++){
      if(lessThan(v[j+1],  v[j])) std::swap(v[j], v[j+1]);
    }
  }
}

// забележете че тук сложността зависи от сложността lessThan по следния начин:
// T(sortBy) = O(n^2) * T(lessThan)
// S(sortBy) = O(1) * S(lessThan) !! тук разчитаме, че динамичната памет в lessThan се освобождава в lessThan



