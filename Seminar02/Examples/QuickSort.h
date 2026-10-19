#pragma once
#include <vector>


template<class T>
size_t partition(std::vector<T>& v, size_t begin, size_t end){

    T pivot = v[begin];

    // това ще използваме като индекса, на който трябва да стои следващия елемент < от pivot
    size_t ind = begin + 1; // бях забравил + 1 :)

    // в цикъла ще пропуснем обхождането на pivot
    for(size_t i = begin + 1; i < end - begin; i++){
        if(v[i] < pivot){
            // поставяме елемента по-малък от pivot на позицията му 
            std::swap(v[i], v[ind]);
            ind++; // и преместваме индекса с едно напред
        }
    }

    // v[ind - 1] <= pivot = v[begin], защото не сме го местили
    // освен това v[ind - i] <= pivot за всяко i=1,2, ..., ind, така че
    // тази позиция е коректна
    std::swap(v[begin], v[ind - 1]);

    return ind - 1;
}

// сложност по време: О(n)
// сложност по памет: O(1)

// помощна функция, която ще приема допълнителни параметри
template <class T>
void quickSort(std::vector<T>& v, size_t begin, size_t end){
    if(end - begin <= 1) return;

    size_t p = partition(v, begin, end);

    // пропускаме елемента на индекс p, защото той е "на място"
    quickSort(v, begin, p);
    quickSort(v, p + 1, end);
}

template <class T>
void quickSort(std::vector<T>& v){
    quickSort(v, 0, v.size());
}

// сложност по време: O(n*log n)
// сложност по памет: O(log n) - заради рекурсивния стек
