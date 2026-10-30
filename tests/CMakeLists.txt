include(FetchContent)

# 1. Подключаем GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Для Windows (не обязательно для WSL, но полезно)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 2. Создаём исполняемый файл тестов
add_executable(matrix_tests test_matrix.cpp ../src/matrix.cpp)

# 3. Указываем, где искать matrix.h
target_include_directories(matrix_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 4. Линкуем с GoogleTest
target_link_libraries(matrix_tests PRIVATE GTest::gtest_main)

# 5. Регистрируем тесты в CTest
include(GoogleTest)
gtest_discover_tests(matrix_tests)

