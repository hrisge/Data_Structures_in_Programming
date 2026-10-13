#pragma once
#include <stdexcept>

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

// сложност по време: O(matrix1.rows() * matrix2.cols() * matrix1.cols())
// сложност по памет: O(matrix1.rows() * matrix2.cols())