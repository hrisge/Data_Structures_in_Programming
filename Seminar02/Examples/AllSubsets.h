#pragma once
#include <vector>
#include <iostream>

template<class T>
void printAllSubsetsHelper(const std::vector<T> &v, std::vector<bool>& contains, size_t depth){

  if(depth >= v.size()){
    std::cout << "{" << " "; 

    for(size_t i = 0; i < v.size(); i++){
      if(contains[i]) std::cout << v[i] << " ";
    }

    std::cout << "}" << std::endl;

    return;
  }

  
  contains[depth] = 0;
  printAllSubsetsHelper(v, contains, depth+1);
  contains[depth] = 1;
  printAllSubsetsHelper(v, contains, depth+1);
}

template <class T>
void printAllSubsets(const std::vector<T>& v){
  std::vector<bool> contains(v.size());

  printAllSubsetsHelper(v, contains, 1);
  contains[0] = 1;
  printAllSubsetsHelper(v, contains, 1);

}

// сложност по време: O(2^n)
// сложност по памет: O(n)