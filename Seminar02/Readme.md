# Сложности на рекурсивни алгоритми и сортировки - 13.10.2026



## Преговор от миналия път
Определете сложностите на следните алгоритми:

```
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

```
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

```
int fact(int n){
	if(n == 0) return 1;
	return n * fact(n-1);
}
```

```
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

Нека А е масив и съдържа елементите $a_0, a_1, ..., a_{n-1}$ и нека $m = (n - 1) / 2$ е индекса на средния елемент. Подредете масива, така че да отговаря на следните условия:

- $a_m \leq a_{m-1} \ \& \ a_m \leq a_{m+1}$
- $a_0 \leq a_1 \leq ... \leq a_{m-1}$
- $a_{n-1} \leq a_{n-2} \leq ... \leq a_{m+1}$


### Зад 2.

Реализирайте функцията ```void sortBy(std::vector<T>& v, <подходящ тип> lessThan)```, която сортира масив по подаден компаратор.
