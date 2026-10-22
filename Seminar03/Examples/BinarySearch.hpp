#pragma once
#include <functional>

// двоично търсене с рекурсия
template <class Container, class T>
int binarySearchRec(const Container& arr, const T& target){

  // тук right е индексът на елемента след последния
  std::function<int(int, int)> binarySearchHelper =
  [&](int left, int right){
    if(left >= right) return -1;

    // намираме индекса на средния елемент
    int mid = (right - left) / 2 + left;

    // ако търсения елемент е по средата връщаме средния индекс
    if(target == arr[mid]) return mid;
    // ако е по-голям от елемента по средата ще търсим след средния елемент
    else if(target > arr[mid]) return binarySearchHelper(mid + 1, right);
    // ако е по-малък ще търсим преди средния
    else return binarySearchHelper(left, mid);
  };

  return binarySearchHelper(0, arr.size());
}

// сложност по време: O(log n)
// сложност по памет: O(log n) - заради рекурсивния стек

// итеративно двоично търсене
template <class Container, class T>
int binarySearch(const Container& arr, const T& target){

  int left = 0;
  // тук right е индекса на последния елемент
  int right = arr.size() - 1;

  while(left <= right){
    int mid = (right - left) / 2 + left;
    if(arr[mid] == target) return mid;
    else if(target > arr[mid]) left = mid + 1;
    else right = mid - 1;
  }

  return -1;
}

// сложност по време: O(log n)
// сложност по памет: О(1)

// няма значение кой от двата варианта за right ще изберете, но забележете разликите в кода