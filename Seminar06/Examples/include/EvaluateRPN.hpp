#pragma once
#include "LinkedList.hpp"
#include "Stack.hpp"
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

bool isOperator(const std::string& s){
  return s == "+" || s == "-" || s == "*" || s == "/";
}

bool isNumber(const std::string& s){
  for(int i = 0; i < s.size(); i++){
    if(s[i] > '9' || s[i] < '0') return false;
  }
  return true;
}

// приемаме, че ще се извиква само за валиден оператор
std::function<int(int, int)> getOperator(const std::string& s){
  switch(s[0]){
      case '+': return std::plus<int>();
      case '-': return std::minus<int>();
      case '*': return std::multiplies<int>();
      case '/': return std::divides<int>();
    }
}

// тук използваните типове, подобно на std::less, са типове на функционални обекти,
// които извикват съответния оператор за подадения тип
// например: std::plus<int>() <=> [](int a, int b) {return a + b;}; 
// (не е точно така, но може да си го представяте така. Може да видите повече в cppreference)
// или: std::plus<int>()(a, b) <=> a + b, за a, b от тип int

// RPN = Reverse Polish Notation
int evaluateRPN(const std::vector<std::string>& expr){
  if(expr.empty()) return 0;

  Stack<std::string> stack;

  std::function<int()> getNextNumber = 
  [&](){
      // ако стекът е празен няма какво да извадим
      if(stack.empty()) throw std::invalid_argument("invalid expression");
      // взимаме върха на стека и го превръщаме в цяло число
      int result = std::atoi(stack.peek().c_str());
      stack.pop();
      return result;
  };

  for(std::string s : expr){
    // ако стигнем до оператор, изваждаме последните две числа и прилагаме оператора
    if(isOperator(s)){
      int a = getNextNumber();
      int b = getNextNumber();
      // тук трябва да обърнем реда, защото стека ги изкарва наобратно
      stack.push(std::to_string(getOperator(s)(b, a)));
    }
    // ако стигнем до число, го слагаме в стека
    else if(isNumber(s)){
      stack.push(s);
    }
    // ако низа не е нито число, нито оператор хвърляме грешка
    else{
      throw std::invalid_argument(
        "there is a string in the expression that is not a number or operator");
    }
    
  }

  // ако в стека има повече от един елемент, изразът е невалиден
  if(stack.size() > 1) throw std::invalid_argument("invalid expression");
  // връщаме елемента на върха на стека
  return std::atoi(stack.peek().c_str());
}
