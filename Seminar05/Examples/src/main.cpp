#include <iostream>
#include "LinkedList.hpp"
#include "SelectionSort.hpp"

int main() {
    LinkedList<int> ll;
    for(int i = 0; i < 10; i++){
        ll.push_back(i);
    }

    for(LinkedList<int>::iterator it = ll.begin(); it != ll.end(); ++it){
        if(*it == 5) ll.insert_after(6, it);
    }

    ll.reverse();
    for(int x : ll){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // 9 8 7 6 6 5 4 3 2 1 0

    std::cout << 
    ll.foldr<int>([](int x, int y){return x+ y;}, 0)
    << std::endl;
    // 51
   sort(ll.begin(), ll.end());
   for(int x : ll){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // 0 1 2 3 4 5 6 6 7 8 9
    LinkedList<int> ll2 = ll.map<int>([](int x){return x*x;});
    for(int x : ll2){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // 0 1 4 9 16 25 36 36 49 64 81

    LinkedList<int> ll3 = ll2.filter([](int x){return x%2 == 0;});
    for(int x : ll3){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // 0 4 16 36 36 64

    // може и така
    LinkedList<int> ll4 = ll
    .map<int>([](int x){return x*x;})
    .filter([](int x){return x%2 == 0;});

    for(int x : ll4){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // 0 4 16 36 36 64
}
