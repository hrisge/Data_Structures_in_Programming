#pragma once
#include <utility>
#include <cstddef>
#include <functional>

template <class T>
class DoublyLinkedList{

  struct Node{
    T data;
    Node* next;
    Node* prev;

    Node(const T& data, Node* next = nullptr, Node* prev = nullptr) 
    : data(data), next(next), prev(prev) {}
  };

  Node* m_begin;
  Node* m_end;
  size_t m_size;

  void copy(const DoublyLinkedList& other){
    Node* it = other.m_begin;

    while(it){
      push_back(it->data);
      it = it->next;
    }
  }
  void move(DoublyLinkedList&& other){
    m_begin = other.m_begin;
    m_end = other.m_end;
    m_size = other.m_size;

    other.m_begin = nullptr;
    other.m_end = nullptr;
    other.m_size = 0;
    
    
    /* може и така
      std::swap(m_begin, other.m_begin);
      std::swap(m_end, other.m_end);
      std::swap(m_size, other.m_size);
    */
  }
  void free(){
    while(!empty()){
      pop_front();
    }
  }

public:
  
  class iterator{
    Node* pos;
  public:
    iterator(Node* pos) : pos(pos) {}

    bool valid() const {
      return pos;
    }

    operator bool() const {
      return valid();
    }

    iterator& operator++(){
      pos = pos->next;
      return *this;
    }

    bool operator!=(const iterator& other) const {
      return pos != other.pos;
    }

    bool operator==(const iterator& other) const {
      return pos == other.pos;
    }

    T& operator*(){
      return pos->data;
    }

    const T& operator*() const {
      return pos->data;
    }

    friend DoublyLinkedList<T>;
  };

  class reverse_iterator{
    Node* pos;
  public:
    reverse_iterator(Node* pos) : pos(pos) {}

    bool valid() const {
      return pos;
    }

    operator bool() const {
      return valid();
    }

    reverse_iterator& operator++(){
      pos = pos->prev;
      return *this;
    }

    bool operator!=(const reverse_iterator& other) const {
      return pos != other.pos;
    }

    bool operator==(const reverse_iterator& other) const {
      return pos == other.pos;
    }

    T& operator*(){
      return pos->data;
    }

    const T& operator*() const {
      return pos->data;
    }

    friend DoublyLinkedList<T>;
  };


  iterator begin() {
    return m_begin;
  }

  iterator end() {
    return nullptr;
  }

  reverse_iterator rbegin() {
    return m_end;
  }

  reverse_iterator rend() {
    return nullptr;
  }


  DoublyLinkedList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}

  DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList() {
    copy(other);
  }

  DoublyLinkedList(DoublyLinkedList&& other) : DoublyLinkedList() {
    move(std::move(other));
  }

  DoublyLinkedList& operator=(const DoublyLinkedList& other) {
    if(this == &other) return *this;
    free();
    copy(other);

    return *this;
  }

  DoublyLinkedList& operator=(DoublyLinkedList&& other){
    if(this == &other) return *this;
    free();
    move(std::move(other));

    return *this;
  }

  ~DoublyLinkedList(){
    free();
  }

  bool empty() const {
    return m_size == 0;
  }

  size_t size() const {
    return m_size;
  }

  void push_front(const T& element){
    Node* newNode = new Node(element, m_begin);
    m_begin = newNode;
    if(empty()) m_end = newNode;
    else m_begin->prev = newNode;
    ++m_size;
  }

  void push_back(const T& element){
    if(empty()) {
      push_front(element);
      return;
    } 
    Node* newNode = new Node(element, nullptr, m_end);
    m_end->next = newNode; 
    m_end = newNode;
    ++m_size;
  }



  void pop_front() {
    if(empty()) return;

    Node* toDelete = m_begin;
    m_begin = m_begin->next;
    m_begin->prev = nullptr;
    delete toDelete;
    --m_size;

    if(m_size == 0){
      m_end = nullptr;
    }
  }

  void pop_back(){
    if(empty()) return;
    if(m_size == 1){
      pop_front();
      return;
    }

    Node* toDelete = m_end;
    m_end = m_end->prev;
    m_end->next = nullptr;
    delete toDelete;

    --m_size;
  }


  void insert_after(const T& element, iterator it){

    if(empty()) {
      push_front(element);
      return;
    }
    if(!it) {
      return;
    }

    if(it == m_end){
      push_back(element);
      return;
    }
    

    Node* newNode = new Node(element, it.pos->next, it.pos);
    it.pos->next->prev = newNode;
    it.pos->next = newNode;
    ++m_size;
  }

  void remove_after(iterator it) {
    if(m_size <= 1){
       pop_front();
       return;
    }
    if(!it) return;

    if(it.pos->next == m_end){
      m_end = it.pos;
    }

    Node* toDelete = it.pos->next;

    it.pos->next = it.pos->next->next;
    it.pos->next->prev = it.pos;

    delete toDelete;
    --m_size;
  }

  bool contains(const T& element){
    for(const T& cur : *this){
      if(cur == element) return true;
    }
    return false;
  }

  iterator find(const T& element){
    for(iterator it = begin(); it != end(); ++it){
      if(*it == element) return it;
    }
    return nullptr;
  }

  T& operator[](size_t index){
    iterator i = begin();
    for(int j = 0; j < index; j++){
      ++i;
    }
    return *i;
  }

  const T& operator[](size_t index) const {
    iterator i = begin();
    for(int j = 0; j < index; j++){
      ++i;
    }
    return *i;
  }

  void reverse() {

    if(empty()) return;

    std::function<void(Node*)> reverseHelper = 
    [&](Node* cur){
      if(!cur->next){
        m_begin = cur;
        return;
      } 

      reverseHelper(cur->next);
      cur->next->next = cur;
    };

    m_end = m_begin;
    
    reverseHelper(m_begin);
    m_end->next = nullptr;
  }


  template<class R>
  R foldr(const std::function<R(const T&, R&&)>& op, const R& nv) const {
    std::function<R(Node*)> foldrHelper =
    [&](Node* cur){
      if(!cur) return nv;
      return op(cur->data, foldrHelper(cur->next));
    };

    return foldrHelper(m_begin);
  }


  template <class R>
  DoublyLinkedList<R> map(const std::function<R(const T&)>& f) const {
    return foldr<DoublyLinkedList<R>>(
      [&](const T& x,  DoublyLinkedList<R>&& xs){
        xs.push_front(f(x));
        return xs;
      },
      DoublyLinkedList<R>());
  }

  DoublyLinkedList<T> filter(const std::function<bool(const T&)>& f) const {
    return foldr<DoublyLinkedList<T>>(
      [&](const T& x, DoublyLinkedList<T>&& xs){
        if(f(x)) xs.push_front(x);
        return xs;
      },
      DoublyLinkedList<T>()
    );
  }
};