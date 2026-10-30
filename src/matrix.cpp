// src/matrix.cpp
#include "matrix.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace matrix {

namespace {

constexpr int kMaxRowsToShow = 10;
constexpr int kMaxColsToShow = 8;

}  // namespace

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        mat.data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            mat.data[i][j] = 0.0;
        }
    }
    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) return;
    for (int i = 0; i < m.rows; ++i) {
        delete[] m.data[i];
    }
    delete[] m.data;
    // ВАЖНО: m передаётся ПО ЗНАЧЕНИЮ, поэтому вызывающий код должен
    // сам обнулить свою копию указателя, если планирует её использовать.
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix sizes must match for addition");
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < a.cols; ++k) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(2);
    const bool show_summary =
        (m.rows > kMaxRowsToShow || m.cols > kMaxColsToShow);
    const int rows_to_show = show_summary ? kMaxRowsToShow : m.rows;
    const int cols_to_show = show_summary ? kMaxColsToShow : m.cols;

    for (int i = 0; i < rows_to_show; ++i) {
        if (show_summary && i == kMaxRowsToShow / 2 && m.rows > kMaxRowsToShow) {
            std::cout << "  [...]\n";
            continue;
        }
        std::cout << "[";
        for (int j = 0; j < cols_to_show; ++j) {
            if (show_summary && j == kMaxColsToShow / 2 && m.cols > kMaxColsToShow) {
                std::cout << "  ...  ";
                continue;
            }
            std::cout << std::setw(7) << m.data[i][j];
        }
        std::cout << "]\n";
    }
    if (show_summary) {
        std::cout << "Matrix " << m.rows << "x" << m.cols
                  << " (showing " << rows_to_show << "x" << cols_to_show << ")\n";
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Data pointer is null");
    }
    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            m.data[i][j] = data[i * cols + j];
        }
    }
    return m;
}

// ==================== ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ №3 ====================

Matrix matrix_identity(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Identity matrix size must be positive");
    }
    Matrix m = create_matrix(size, size);
    for (int i = 0; i < size; ++i) {
        m.data[i][i] = 1.0;
    }
    return m;
}

}  // namespace matrix