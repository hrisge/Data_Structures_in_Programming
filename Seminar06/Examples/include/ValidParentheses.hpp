#pragma once

#include "Stack.hpp"
#include <functional>
#include <string>
#include <vector>

bool validParentheses(const std::string& str) {

  // Ще си направим "таблица" с видовете скоби за да можем лесно да работим с тях
  // по редовете имаме категория отваряща/затваряща, а по колоните
  // имаме категория вид - кръгла, квадратна, къдрава
  std::vector<char> openingBrackets = {'(', '[', '{'};
  std::vector<char> closingBrackets = {')', ']', '}'};

  // намира индекса, на който е даден елемент ако съществува и 
  // v.size(), ако не съществува
  std::function<size_t(char, const std::vector<char>&)> find = 
  [&](char c, const std::vector<char>& v)-> size_t {
    for(size_t i = 0; i < v.size(); i++){
      if(c == v[i]) return i;
    }
    return v.size();
  };

  // в стека ще добавяме отварящите скоби
  Stack<char> s;

  for(int i = 0 ; i < str.size(); i++){
    size_t opening = find(str[i], openingBrackets);
    size_t closing = find(str[i], closingBrackets);
    // ако имаме отваряща скоба я добавяме в стека
    if(opening < openingBrackets.size()){
      s.push(str[i]);
    }
    // ако имаме затваряща скоба ще проверим дали изпълнява изискванията
    else if(closing < closingBrackets.size()){
      // няма съответна отваряща скоба която я предхожда
      if(s.empty()) return false; 
      // последната скоба, която трябва да се затвори е от различен тип
      // (в различни колонки на таблицата са)
      else if(find(s.peek(), openingBrackets) != closing) return false; 
      else{
        // отварящата скоба е правилно затворена и продължаваме към следващата
        s.pop(); 
      }
    }
    // ако символа не е нито отваряща, нито затваряща скоба няма нужда да правим нещо
  }
  // ако стекът е празен, значи сме затворили всички отварящи скоби, иначе израза не е валиден
  return s.empty(); 
}