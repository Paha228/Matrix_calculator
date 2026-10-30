#include <gtest/gtest.h>

#include <stdexcept>

#include "matrix.h"

// ---------- Базовые функции ----------

TEST(MatrixTest, CreateMatrix_NormalCase) {
    matrix::Matrix A = matrix::create_matrix(3, 4);
    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
    matrix::free_matrix(A);
}

TEST(MatrixTest, Addition_NormalCase) {
    auto A = matrix::create_matrix(2, 2);
    auto B = matrix::create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    auto C = matrix::matrix_add(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

TEST(MatrixTest, Multiplication_NormalCase) {
    auto A = matrix::create_matrix(2, 2);
    auto B = matrix::create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    auto C = matrix::matrix_multiply(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

// ---------- Граничные случаи ----------

TEST(MatrixTest, CreateMatrix_MinimumSize) {
    auto A = matrix::create_matrix(1, 1);
    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);
    matrix::free_matrix(A);
}

TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    auto A = matrix::create_matrix(1, 3);
    auto B = matrix::create_matrix(3, 1);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    B.data[0][0] = 4; B.data[1][0] = 5; B.data[2][0] = 6;
    auto C = matrix::matrix_multiply(A, B);
    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);
    matrix::free_matrix(A);
    matrix::free_matrix(B);
    matrix::free_matrix(C);
}

// ---------- Некорректные случаи ----------

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(matrix::create_matrix(0, 3), std::invalid_argument);
}

TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(matrix::create_matrix(3, -1), std::invalid_argument);
}

TEST(MatrixTest, Addition_SizeMismatch) {
    auto A = matrix::create_matrix(2, 2);
    auto B = matrix::create_matrix(3, 3);
    EXPECT_THROW(matrix::matrix_add(A, B), std::invalid_argument);
    matrix::free_matrix(A);
    matrix::free_matrix(B);
}

TEST(MatrixTest, Multiplication_SizeMismatch) {
    auto A = matrix::create_matrix(2, 3);
    auto B = matrix::create_matrix(2, 2);
    EXPECT_THROW(matrix::matrix_multiply(A, B), std::invalid_argument);
    matrix::free_matrix(A);
    matrix::free_matrix(B);
}

// ---------- ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ №3 ----------

TEST(MatrixTest, Identity_Size1) {
    auto I = matrix::matrix_identity(1);
    EXPECT_EQ(I.rows, 1);
    EXPECT_EQ(I.cols, 1);
    EXPECT_DOUBLE_EQ(I.data[0][0], 1.0);
    matrix::free_matrix(I);
}

TEST(MatrixTest, Identity_Size5) {
    constexpr int n = 5;
    auto I = matrix::matrix_identity(n);
    EXPECT_EQ(I.rows, n);
    EXPECT_EQ(I.cols, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            EXPECT_DOUBLE_EQ(I.data[i][j], (i == j) ? 1.0 : 0.0);
        }
    }
    matrix::free_matrix(I);
}

TEST(MatrixTest, Identity_MultiplicationKeepsMatrix) {
    // A * I = A
    auto A = matrix::create_matrix(3, 3);
    A.data[0][0] = 7; A.data[1][1] = 8; A.data[2][2] = 9;
    auto I = matrix::matrix_identity(3);
    auto R = matrix::matrix_multiply(A, I);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(R.data[i][j], A.data[i][j]);
    matrix::free_matrix(A);
    matrix::free_matrix(I);
    matrix::free_matrix(R);
}

TEST(MatrixTest, Identity_InvalidSize) {
    EXPECT_THROW(matrix::matrix_identity(0), std::invalid_argument);
    EXPECT_THROW(matrix::matrix_identity(-3), std::invalid_argument);
}