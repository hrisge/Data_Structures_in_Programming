# Сложности на рекурсивни алгоритми и сортировки - 13.10.2026



## Преговор от миналия път
Определете сложностите на следните алгоритми:

```cpp
size_t digitsCount(int n){
  if(n == 0) return 1;
  size_t result = 0;

  while(n != 0){
    result++;
    n /= 10;
  }

  return result;
}
```

```cpp
Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
  if(matrix1.cols() != matrix2.rows()) throw std::runtime_error("matrices cannot be multiplied");

  Matrix result(matrix1.rows(), matrix2.cols());

  for(int i = 0; i < matrix1.rows(); i++){
    for(int j = 0; j < matrix2.cols(); j++){
      for(int k = 0; k < matrix1.cols(); k++){
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  return result;
}
```

## Примери за рекурсивни алгоритми

```cpp
int fact(int n){
	if(n == 0) return 1;
	return n * fact(n-1);
}
```

```cpp
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
```

## Задача за самоподготовка

### Зад 1.

Нека $А$ е масив и съдържа елементите $a_0, a_1, ..., a_{n-1}$ и нека $m = (n - 1) / 2$ е индекса на средния елемент. Напишете алгоритъм, който "сортира" $А$ по следния начин:

- $a'_{m \pm i} \geq a'_{m \pm j} \iff i < j, \ m \pm i, \ m\pm j \in \{0...n-1\}$

Където $a'_i$ са елементите на масива след изпълнението на алгоритъма.

Или неформално - подредете елементите под формата на пирамида, където най-големият елемент е по средата и елементите на всяко "стъпало" са по-малки от елементите на горните стъпала. Например:

```
Вход: {10, 12, 32, 24, 15, 26, 17, 18, 19}
Изход: 10 15 18 24 32 26 19 17 12

	    32
	 24    26
      18	  19
   15		     17
10		        12

// Забележка: Подреждането не е единствено
// Не е нужно да отпечатвате масива, както в примера
```




### Зад 2.

Реализирайте функцията ```void sortBy(std::vector<T>& v, <подходящ тип> lessThan)```, която сортира масив по подаден компаратор.
