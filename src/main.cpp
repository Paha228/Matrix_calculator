// src/main.cpp
#include <iostream>

#include "matrix.h"

int main() {
    // Демонстрация базовых операций
    matrix::Matrix A = matrix::create_matrix(2, 2);
    matrix::Matrix B = matrix::create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    matrix::Matrix sum = matrix::matrix_add(A, B);
    matrix::Matrix product = matrix::matrix_multiply(A, B);

    std::cout << "Matrix A:\n";
    matrix::print_matrix(A);
    std::cout << "Sum A+B:\n";
    matrix::print_matrix(sum);
    std::cout << "Product A*B:\n";
    matrix::print_matrix(product);

    // Индивидуальное задание: единичная матрица 4x4
    std::cout << "Identity(4):\n";
    matrix::Matrix I = matrix::matrix_identity(4);
    matrix::print_matrix(I);

    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(sum);
    matrix::free_matrix(product);
    matrix::free_matrix(I);
    return 0;
}