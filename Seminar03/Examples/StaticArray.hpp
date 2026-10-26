#pragma once
#include <cstdlib>
#include <utility>

template <class T, size_t capacity>
class StaticArray {
  T arr[capacity];
  size_t m_size;

public:

  StaticArray() : m_size(0){}

  StaticArray(const T* arr, size_t size) : m_size(0) {
    if(size > capacity) return;
    for(size_t i = 0; i < size; i++){
      push(arr[i]);
    }
  }

  bool empty() const {
    return m_size == 0;
  }

  size_t size() const {
    return m_size;
  }

  void push(const T& element){
    if(m_size >= capacity) return;
    arr[m_size++] = element;
  }

  void pop(){
    if(m_size <= 0) return;
    --m_size;
  }

  void insert(size_t index, const T& element){
    if(index >= capacity || index < 0) return;
    if(m_size + 1 >= capacity) return;
    push(element);
    for(size_t i = m_size - 1; i > index ; i--){
      std::swap(arr[i], arr[i - 1]);
    }
  }

  void remove(size_t index){
    if(index >= capacity || index < 0) return;
    if(m_size <= 0) return;

    for(size_t i = index; i < m_size - 1 ; i++){
      std::swap(arr[i], arr[i + 1]);
    }

    pop();
  }

  T& operator[](size_t ind) {
    return arr[ind];
  }

  const T& operator[](size_t ind) const {
    return arr[ind];
  }
};