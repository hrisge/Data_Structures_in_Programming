#pragma once
#include <vector>
#include <iostream>

template <class T>
void pyramid(std::vector<T>& v){

  size_t mid = (v.size()-1)/2;

  for(size_t i = 0; i < v.size(); i++){

    size_t max = mid - ((i + 1)/2)*(i % 2 == 0 ? 1 : -1);

    for(size_t j = i + 1; j < v.size(); j++){
      size_t cur = mid - ((j + 1)/2)*(j % 2 == 0 ? 1 : -1);
      if(v[cur] > v[max]){
        max = cur;
      }
    }
    std::swap(v[mid - ((i + 1) / 2)*(i % 2 == 0 ? 1 : -1)], v[max]);
  }
}

// идеята на решението е да извършим selection sort с модификация:
// когато обхождаме масива, ще заместим i със f(i), където f(i) = mid - ((i + 1) / 2)*(i % 2 == 0 ? 1 : -1) 
// алтернативно функцията може да се запише по следния начин:
/* 

  std::function<size_t(size_t)> get = [&](size_t i) {
      size_t mid = (v.size()-1)/2;
      return mid - ((i + 1)/2)*(i % 2 == 0 ? 1 : -1);
    };

    for(size_t i = 0; i < v.size(); i++){

      size_t max = get(i);

      for(size_t j = i + 1; j < v.size(); j++){
        size_t cur = get(j);
        if(v[cur] > v[max]){
          max = cur;
        }
      }
      std::swap(v[get(i)], v[max]);
    }
  }

*/
// за допълнително упражнение:
// опитайте да реализирате същата задача с различен метод за сортиране,
// за произволна биекция {0...n-1} -> {0...n-1} (приемаме че подадената функция е коректна)