// include/matrix.h
#pragma once

#include <cstddef>

namespace matrix {

/**
 * @brief Структура матрицы.
 *
 * Хранит двумерный динамический массив и его размеры.
 * @warning Память освобождается через free_matrix().
 */
struct Matrix {
    double** data;  ///< Указатель на двумерный массив.
    int rows;       ///< Количество строк.
    int cols;       ///< Количество столбцов.
};

/**
 * @brief Создание матрицы заданного размера.
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Инициализированная нулями матрица.
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 * @note Время выполнения: O(rows * cols).
 * @see free_matrix()
 * @code
 * Matrix A = create_matrix(3, 3);
 * @endcode
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти, занятой матрицей.
 * @param m Матрица, память которой нужно освободить.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Matrix Результат сложения.
 * @exception std::invalid_argument Если размеры не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение двух матриц.
 * @param a Матрица M×N.
 * @param b Матрица N×K.
 * @return Matrix Результат M×K.
 * @exception std::invalid_argument Если cols(a) != rows(b).
 * @note Время выполнения: O(M*N*K).
 * @warning Результат нужно освобождать через free_matrix().
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы в консоль с форматированием.
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из одномерного массива.
 * @param data Указатель на массив данных (не nullptr).
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Новая матрица с данными из массива.
 * @exception std::invalid_argument Если параметры некорректны.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

// ==================== ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ №3 ====================

/**
 * @brief Создание единичной матрицы заданного размера.
 *
 * На главной диагонали — 1, остальные элементы — 0.
 *
 * @param size Размер матрицы (size × size), должен быть > 0.
 * @return Matrix Единичная матрица size × size.
 * @exception std::invalid_argument Если size <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 * @note Время выполнения: O(size^2).
 * @see create_matrix(), free_matrix()
 * @code
 * Matrix I = matrix_identity(3);
 * // I = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
 * @endcode
 */
Matrix matrix_identity(int size);

}  // namespace matrix



