#pragma once
#include <cstddef>

size_t digitsCount(int n){
  if(n == 0) return 1;
  size_t result = 0;

  while(n != 0){
    result++;
    n /= 10;
  }

  return result;
}

// сложност по време: O(log n)
// сложност по памет: О(1)