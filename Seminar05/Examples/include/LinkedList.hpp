#pragma once
#include <utility>
#include <cstddef>
#include <functional>

template <class T>
class LinkedList{

  struct Node{
    T data;
    Node* next;

    Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
  };

  Node* m_begin;
  Node* m_end;
  size_t m_size;

  void copy(const LinkedList& other){
    Node* it = other.m_begin;

    while(it){
      push_back(it->data);
      it = it->next;
    }
  }
  void move(LinkedList&& other){
    m_begin = other.m_begin;
    m_end = other.m_end;
    m_size = other.m_size;

    other.m_begin = nullptr;
    other.m_end = nullptr;
    //1. бях забравил да зануля other.m_size() 
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

    friend LinkedList<T>;
  };


  iterator begin() {
    return m_begin;
  }

  iterator end() {
    return nullptr;
  }

  // ако искаме константни begin() и end() методи ще трябва да си направим константен итератор
  // const_iterator begin() const {
  //   return m_begin;
  // }

  LinkedList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}

  //2. бях забравил да извикам default конструктора в copy и move конструкторите
  LinkedList(const LinkedList& other) : LinkedList() {
    copy(other);
  }

  LinkedList(LinkedList&& other) : LinkedList() {
    move(std::move(other));
  }

  LinkedList& operator=(const LinkedList& other) {
    if(this == &other) return *this;
    free();
    copy(other);

    return *this;
  }

  LinkedList& operator=(LinkedList&& other){
    if(this == &other) return *this;
    free();
    move(std::move(other));

    return *this;
  }

  ~LinkedList(){
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
    ++m_size;
  }

  void push_back(const T& element){
    if(empty()){
      push_front(element);
      return;
    } 
    Node* newNode = new Node(element);
    m_end->next = newNode; // (*m_end).next <=> m_end->next
    m_end = newNode;
    ++m_size;
  }



  void pop_front() {
    if(empty()) return;

    // запазваме begin във временна променлива, за да не загубим началото на списъка
    Node* toDelete = m_begin;
    m_begin = m_begin->next;
    delete toDelete;
    --m_size;

    if(m_size == 0){
      m_end = nullptr;
    }
  }

  void pop_back(){
    if(empty()) return;
    if(m_size == 1){
      // ако имаме само един елемент преизползваме логиката за зануляване на указателите от pop_front
      pop_front();
      return;
    }
    // трябва да намерим елемента преди последния, за да можем да го посочим с end след като изтрием последния
    Node* it = m_begin;

    while(it->next != m_end){
      it = it->next;
    }

    delete m_end;
    m_end = it;

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
    // ако добавяме след края трябва да променим m_end
    if(it == m_end){
      push_back(element);
      return;
    }


    Node* newNode = new Node(element, it.pos->next);
    it.pos->next = newNode;
    ++m_size;
  }

  void remove_after(iterator it){
    if(m_size <= 1){
       pop_front();
       return;
    }
	if(!it) return;
    // ако премахваме последния елемент също трябва да променим m_end
    if(it.pos->next == m_end){
      m_end = it.pos;
    }
 

    Node* toDelete = it.pos->next;

    it.pos->next = it.pos->next->next;

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

  // забележете разликата с масива в operator[]
  // тук нямаме пряк достъп до елементите за константно време
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
        // cur е последния елемент и слагаме begin да сочи към него
        // защото след като обърнем списъка, той трябва да стане първи
        m_begin = cur;
        return;
      } 

      // обръщаме остатъка от масива
      reverseHelper(cur->next);
      // казваме на следващия възел да сочи към текущия
      cur->next->next = cur;
      // cur->next = nullptr; -  може и така вместо ред последния ред от reverse()
    };


    // присвояваме begin на end и в reverseHelper поставяме begin на правилната позиция
    m_end = m_begin;
    
    reverseHelper(m_begin);
    // трябва да пренасочим end->next към nullptr, за да 
    m_end->next = nullptr;
  }


  
  // операцията ни приема const T&, защото не трябва да променя оригиналния списък и
  // R&& за да ползваме move семантики за да избегнем копиране на междинните стойности.
  // На практика единственото копиране тук е на nv
  template<class R>
  R foldr(const std::function<R(const T&, R&&)>& op, const R& nv) const {
    std::function<R(Node*)> foldrHelper =
    [&](Node* cur){
      if(!cur) return nv;
      return op(cur->data, foldrHelper(cur->next));
    };

    return foldrHelper(m_begin);
  }


  // не работеше заради 1. и 2. (коментарите са по-нагоре) 
  template <class R>
  LinkedList<R> map(const std::function<R(const T&)>& f) const {
    return foldr<LinkedList<R>>(
      [&](const T& x,  LinkedList<R>&& xs){
        // тук също може да има подобрение ако се направи push_front с move семантики
        xs.push_front(f(x));
        return xs;
      },
      LinkedList<R>());
  }

  LinkedList<T> filter(const std::function<bool(const T&)>& f) const {
    return foldr<LinkedList<T>>(
      [&](const T& x, LinkedList<T>&& xs){
        if(f(x)) xs.push_front(x);
        return xs;
      },
      LinkedList<T>()
    );
  }

  /* защо работят map и filter написани така?
     map и filter са модификации на функцията copy

    LinkedList<T> copy() const {
      return foldr<LinkedList<T>>(
        [&](const T& x, LinkedList<T>&& xs){
          xs.push_front(x);
          return xs;
        },
        LinkedList<T>()
      );
    }
    Ако разберем как работи тя, не би трябвало да имаме проблем с разбирането на map и filter

    Нека свързания списък има елемента а_1, a_2, ..., a_n
    Нулевата стойност е празния списък, така че на 1-ва стъпка имаме []
    За 2-ра стъпка изпълняваме операцията върху a_n и [] и получаваме [a_n]
    За 3-та стъпка изпълняваме операцията върху a_(n-1) и [a_n] и получаваме [a_(n-1), a_n]
    .
    .
    За k-та стъпка изпълняваме операцията върху a_(n - k + 2) и [a_(n - k + 3), ..., a_n]
    и получаваме [a_(n - k + 2), ..., a_n]
    .
    .
    За (n+1)-та стъпка изпълняваме операцията върху a_1 и [a_2, ..., a_n] и получаваме [a_1, ..., a_n],
    което е точно първоначалния списък.

    Сега за map вместо елементите a_k ще добавяме стойностите f(a_k) - резултата от изпълнението на функцията
    подадена в map с аргумент a_k
    
    За filter - за елемент a_k ще проверяваме дали изпълнява предиката f подаден във filter
    ако го изпълнява ще изпълним операцията с a_k и акумулирания до сега списък
    иначе връщаме акумулирания до сега списък без да го променяме
  */

  /* други варианти за map и filter (по-малко функционални)

    template <class R>
    LinkedList<R> map(const std::function<R(const T&)>& f) const {
      LinkedList<R> result;
      for(const T& x : *this){
        result.push_back(f(x));
      }
      return result;
    }

    LinkedList<T> filter(const std::function<bool(const T&)>& f) const {
      LinkedList<T> result;
      for(const T& x : *this){
        if(f(x)) result.push_back(x);
      }
      return result;
    }
  */
};



