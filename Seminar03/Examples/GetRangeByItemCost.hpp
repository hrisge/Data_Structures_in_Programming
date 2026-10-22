#pragma once
#include <utility>
#include <string>
#include <vector>
#include <functional>

template <class Container, class T>
int binarySearchFirst(const Container& arr, const T& target, const std::function<bool(const T&, const T&)>& lessThan = std::less<T>()){
// std::less е тип на функционален обект, който се използва за извикване на operator< на елементи от тип T
// може да прочетете повече в cppreference
  int left = 0;
  int right = arr.size() - 1;

  // a = b <=> !(a < b) && !(a > b) - от свойствата на линейната наредба
  // съответно ако lessThan не е линейна наредба функцията няма да работи коректно
  std::function<bool(const T&, const T&)> equals = 
  [&](const T& a, const T& b){
    return !lessThan(a , b) && !lessThan(b, a);
  };

  while(left <= right){
    int mid = (right - left) / 2 + left;
    if(equals(arr[mid], target)){
      // понеже масива е сортиран, ако има повтарящи се елементи, те ще са последователни
      // тогава е достатъчно, когато има повтарящ се елемент преди този, който сме открили
      // да търсим отново измежду елементите преди него
      if(mid > 0 && equals(arr[mid - 1], arr[mid])) right = mid - 1;
      else return mid;
    } 
    else if(lessThan(arr[mid], target)) left = mid + 1;
    else right = mid - 1;
  }

  // ако не е намерен елемента връщаме позицията, на която би стоял
  return left;
}


template <class Container, class T>
int binarySearchLast(const Container& arr, const T& target, const std::function<bool(const T&, const T&)>& lessThan = std::less<T>()){

  int left = 0;
  int right = arr.size() - 1;

  std::function<bool(const T&, const T&)> equals = 
    [&](const T& a, const T& b){
      return !lessThan(a , b) && !lessThan(b, a);
    };

  while(left <= right){
    int mid = (right - left) / 2 + left;
    // аналогично на горното само че този път ще търсим измежду елементите след открития
    if(equals(arr[mid], target)){
      if(mid < arr.size() - 1 && equals(arr[mid + 1], arr[mid])) left = mid + 1;
      else return mid + 1; // + 1, защото искаме елемента след последния
    } 
    else if(lessThan(arr[mid], target)) left = mid + 1;
    else right = mid - 1;
  }
 
  return left;
}

// Забележка: Би било грешно да търсим първото(или последното) срещане на елемента по следния начин:
/*
template <class Container, class T>
int binarySearchFirst(const Container& arr, const T& target){

  int left = 0;
  int right = arr.size() - 1;

  while(left <= right){
    int mid = (right - left) / 2 + left;
    if(arr[mid] == target){

      // разликата с предходния код е тук
      while(mid > 0 && arr[mid] == arr[mid - 1]) mid--;
      //

      else return mid;
    } 
    else if(target > arr[mid]) left = mid + 1;
    else right = mid - 1;
  }

  return -1;
}
*/
// По този начин написан алгоритъма има сложност O(n) в най-лошия случай - когато масива съдържа само един елемент, който се повтаря n пъти
// (Алгоритъмът дава правилен отговор, но няма да спазим условието за времева сложност)

template <class Container, class T>
std::pair<size_t, size_t> getRange(const Container& arr, const T& min, const T& max, const std::function<bool(const T&, const T&)> lessThan = std::less<T>()){
  // втория елемент на наредената двойка е индекса на елемента след последния!
  return {binarySearchFirst(arr, min, lessThan), binarySearchLast(arr, max, lessThan)};
}

struct Item{
  std::string name;
  size_t cost;
};

// желаната функция може да изглежда например така:

template <class Container>
std::pair<size_t, size_t> getRangeByItemCost(const Container &arr, size_t min, size_t max){
  Item minItem = {"", min};
  Item maxItem = {"", max};
  return getRange<Container, Item>(arr, minItem, maxItem, [&](const Item& item1, const Item& item2){return item1.cost < item2.cost;});
}