// test-utils.h

#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include "column.h"
#include <string>

extern int billboard_100_rank[];
extern std::string billboard_100_songs[];
extern std::string billboard_100_artists[];
extern bool billboard_100_awards[];
extern int billboard_100_last_week[];
extern int billboard_100_peak[];
extern int billboard_100_weeks_on_chart[];

inline void print_test_case_number(int number) {
  std::cout << ">>>>>>>>>>> Case " << number << " <<<<<<<<<<<" << std::endl;
}

inline void print_test_name(std::string name) {
  std::cout << "====== " << name << " ======" << std::endl;
}

template <typename T>
void print_info(const Column<T>& column) {
  std::cout << "* Original size of #" << column.get_size() << '#' << std::endl;
  std::cout << "* Original capacity of #" << column.get_capacity() << '#' << std::endl;
}

template <typename T>
void print_info(const Column<T>& first, const Column<T>& second) {
  std::cout << "* first: Original size of #" << first.get_size() << '#' << std::endl;
  std::cout << "* first: Original capacity of #" << first.get_capacity() << '#' << std::endl;
  std::cout << "* second: Original size of #" << second.get_size() << '#' << std::endl;
  std::cout << "* second: Original capacity of #" << second.get_capacity() << '#' << std::endl;
}

template <typename T>
void print_info(const Column<T>& first, const T& second) {
  std::cout << "* first: Original size of #" << first.get_size() << '#' << std::endl;
  std::cout << "* first: Original capacity of #" << first.get_capacity() << '#' << std::endl;
  std::cout << "* second: A single value being #" << second << '#' << std::endl;
}

template <typename T>
Column<T> test_capacity_expansion(T default_value, int size,
                                  int new_capacity, int new_size,
                                  const T* data, std::string name,
                                  bool silent=true) {
  print_test_name("Capacity Reservation & Exapansion Test");
  Column<T> column(default_value, size, data, name);
  print_info(column);
  if (new_capacity > 0) {
    std::cout << "* Reserve a capacity of #" << new_capacity << '#' << std::endl;
    column.reserve_capacity(new_capacity);
  }
  if (new_size > 0) {
    std::cout << "* Expand size to #" << new_size << '#' << std::endl;
    column.expand_size(new_size);
  }
  if (!silent) {
    std::cout << column << std::endl;
  }
  return column;
}

template <typename T>
void test_append(Column<T>& first, Column<T>& second) {
  print_test_name("Append Test");
  print_info(first, second);
  first.append(second);
  std::cout << first << std::endl;
}

template <typename T>
void test_copy_assignment(Column<T>& first, Column<T>& second) {
  print_test_name("Copy Assignment Test");
  print_info(first, second);
  first = second;
  std::cout << first << std::endl;
}

template <typename T>
void test_addition(Column<T>& first, Column<T>& second) {
  print_test_name("Addition Test");
  print_info(first, second);
  std::cout << (first + second) << std::endl;
}

template <typename T>
void test_addition_assignment(Column<T>& first, Column<T>& second) {
  print_test_name("Addition Assignment Test");
  print_info(first, second);
  std::cout << (first += second) << std::endl;
}

template <typename T>
void test_equality(const Column<T>& first, const Column<T>& second) {
  print_test_name("Equality Test");
  print_info(first, second);
  std::cout << (first == second) << std::endl;
}

template <typename T>
void test_less_than(const Column<T>& first, const Column<T>& second) {
  print_test_name("Less than Test");
  print_info(first, second);
  std::cout << (first < second) << std::endl;
}

template <typename T>
void test_equality(const Column<T>& first, const T& second) {
  print_test_name("Equality Test");
  print_info(first, second);
  std::cout << (first == second) << std::endl;
}

template <typename T>
void test_less_than(const Column<T>& first, const T& second) {
  print_test_name("Less than Test");
  print_info(first, second);
  std::cout << (first < second) << std::endl;
}

template <typename T>
void test_negate(const Column<T>& column) {
  print_test_name("Negate Test");
  print_info(column);
  std::cout << (!column) << std::endl;
}

template <typename T>
void test_logical_and(const Column<T>& first, const Column<T>& second) {
  print_test_name("Logical AND Test");
  print_info(first, second);
  std::cout << (first && second) << std::endl;
}

template <typename T>
void test_basic_array_indexing_read(const Column<T>& column) {
  print_test_name("Basic Array Indexing Test (Read)");
  print_info(column);
  for (int i = 0; i < column.get_size(); i++) {
    std::cout << "Item at index " << i << ": " << column[i] << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
void test_negative_indexing_read(const Column<T>& column) {
  print_test_name("Negative Indexing Test (Read)");
  print_info(column);
  for (int i = 1; i <= column.get_size(); i++) {
    std::cout << "Item at index " << -i << ": " << column[-i] << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
void test_basic_array_indexing_write(Column<T>& column) {
  print_test_name("Basic Array Indexing Test (Write)");
  print_info(column);
  for (int i = 0; i < column.get_size(); i++) {
    column[i] += column[i];
  }
  std::cout << column << std::endl;
}

template <typename T>
void test_boolean_indexing(const Column<T>& column, const Column<bool>& selector) {
  print_test_name("Boolean Indexing");
  print_info(column);
  std::cout << column[selector] << std::endl;
}

template <typename T>
void test_integer_indexing_with_conversion_to_string(const Column<T>& column) {
  print_test_name("Integer Indexing with Conversion to std::string");
  print_info(column);
  for (int i = 0; i < column.get_size(); i++) {
    std::string str = column.as_string_at(i);
    std::cout << "Item at index " << i << " as string: " << str << std::endl;
  }
  std::cout << std::endl;
}

#endif  // TEST_UTILS_H_
