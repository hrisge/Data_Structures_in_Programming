#pragma once
#include <vector>
#include <functional>

template <class T>
void mergeSort(std::vector<T>& v){

  std::vector<T> buffer(v.size());

  // използването на ламбда функции е един начин за скриване на помощните функции от външните потребители
  
  std::function<void(size_t, size_t, size_t, size_t)> merge = 
  [&](size_t begin1, size_t end1, size_t begin2, size_t end2){
    size_t startSave = begin1;
    size_t k = 0;

    while(begin1 < end1 && begin2 < end2){
      if(v[begin1] < v[begin2]){
        buffer[k] = v[begin1];
        begin1++;
      }
      else{
        buffer[k] = v[begin2];
        begin2++;
      }
      k++;
    }

    while(begin1 < end1){
      buffer[k] = v[begin1];
      begin1++;
      k++;
    }

    while(begin2 < end2){
      buffer[k] = v[begin2];
      begin2++;
      k++;
    }

    for(size_t i = startSave; i < end2; i++){
      v[i] = buffer[i - startSave];
    }
  };

  std::function<void(size_t, size_t)> mergeSortHelper = [&](size_t begin, size_t end) {
    if(begin + 1 >= end) return;
    size_t middle = begin + (end - begin) / 2;

    mergeSortHelper(begin, middle);
    mergeSortHelper(middle, end);
    
    merge(begin, middle, middle, end);
  };

  mergeSortHelper(0, v.size());
}