#include <vector>

// сливане на два сортирани масива
template <class T>
void merge(std::vector<T>& v, std::vector<T>& buffer, size_t begin, size_t mid,
     size_t end)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t size1 = mid - begin;
    size_t size2 = end - mid;

    while(i < size1 && j < size2){
        if(v[begin + i] < v[mid + j]){
            buffer[k] = v[begin + i];
            i++;
        }
        else{
            buffer[k] = v[mid + j];
            j++;
        }
        k++;
    }

    while(j < size2){
        buffer[k] = v[mid + j];
        k++;
        j++;
    }

    while(i < size1){
        buffer[k] = v[begin + i];
        k++;
        i++;
    }

    for(size_t i = begin; i < end; i++){
        v[i] = buffer[i - begin];
    }
}

// сложност по време: O(n)
// сложност по памет: O(1)

// помощтна функция, която приема допълнителни параметри
template <class T>
void mergeSort(std::vector<T>& v, std::vector<T>& buffer, size_t begin, size_t end){
    if(end - begin <= 1) return;
    
    size_t mid = (end - begin)/2 + begin;

    // сортираме лявата и дясната половина
    mergeSort(v, buffer, begin, mid);
    mergeSort(v, buffer, mid, v.size());

    // след което ги сливаме, защото са вече сортирани
    merge(v, buffer, begin, mid, end);
}

template <class T>
void mergeSort(std::vector<T>& v){
    std::vector<T> buffer(v.size());
    mergeSort(v, buffer, 0, v.size());
}

// сложност по време: O(n*log n)
// сложност по памет: O(n)