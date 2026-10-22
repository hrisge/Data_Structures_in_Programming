#pragma once
#include <vector>


// алгоритъма е модифициран, така че да връща индекс между left и right, на който стои първото число по-голямо от target  
template <class Container, class T>
int binarySearch(const Container& arr, const T& target, int left, int right){

  while(left < right){
    int mid = (right - left) / 2 + left;
    if(arr[mid] == target) return mid + 1; // + 1 защото горното кубче трябва да е строго по-малко от долното
    else if(target > arr[mid]) left = mid + 1;
    else right = mid;
  }

  // връщаме подходящата позиция за кубчето
  return left;
}

size_t leastTowers(const std::vector<size_t>& sizes){

  std::vector<size_t> towers(sizes.size());
  size_t result = 0; // това ще е броя на елементите в масива towers

  // целта на алгоритъма е за кубче i да намерим най-малкото кубче index, върху което можем да го поставим
  // модифицирания ни binary search прави точно това
  for(size_t i = 0; i < sizes.size(); i++){
    // тук можем да използваме binarySearch в масива towers[0...result], защото той винаги е сортиран
    int index = binarySearch(towers, sizes[i], 0, result);

    // ако мястото на кубчето е след всички останали, значи започваме нова кула и трябва да увеличим резултата
    if(index == result) {
      result++; 
    }

    // "поставяме" кубчето i върху кубчето index 
    towers[index] = sizes[i]; 
  }

  return result;
}

