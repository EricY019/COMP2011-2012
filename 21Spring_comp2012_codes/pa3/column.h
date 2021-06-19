// column.h

#ifndef COLUMN_H_
#define COLUMN_H_

#include <string>
#include <iostream>

const int kMinDisplayWidth = 10;
const std::string kDefaultColumnName = "NULL";

template <typename T>
class Column {
  friend class Table;
  template <typename S>
  friend std::ostream& operator<<(std::ostream& os, const Column<S>& column);  // TODO
 public:
  Column() = default;  // for declaring an array of columns
  Column(T default_value, int size, int capacity = -1, std::string name = kDefaultColumnName);  // constructor with size initialization
  Column(T default_value, int size, const T* data, std::string name = kDefaultColumnName);  // type conversion constructor
  Column(const Column<T>& other);  // copy constructor
  Column(const Column<T>& other, const Column<bool>& selector);  // copy constructor, with filitering ability, TODO
  ~Column();
  void reserve_capacity(int new_capacity);  //TODO
  void expand_size(int new_size);  // TODO
  void append(const Column<T>& other);  // TODO
  const Column<T>& operator=(const Column& other);  // copy assignment, TODO
  Column<T> operator+(const Column<T>& other) const;  // addition, TODO
  const Column<T>& operator+=(const Column& other);  // addition assignment, TODO
  Column<bool> operator==(const Column<T>& other) const;  // test equality with column, TODO
  Column<bool> operator<(const Column<T>& other) const;  // test inequality with column, TODO
  Column<bool> operator==(const T& other) const;  // test equality with scalar, TODO
  Column<bool> operator<(const T& other) const;  // test inequality with scalar, TODO
  Column<bool> operator!() const;  // negation, TODO
  Column<bool> operator&&(const Column<T>& other) const;  // logical AND, TODO
  T operator[](int index) const;  // data accessor with negative indexing ability, read-only, TODO
  T& operator[](int index);  // data accessor with negative indexing ability, read-and-write, TODO
  Column operator[](const Column<bool>& selector) const;  // boolean indexing, TODO
  std::string as_string_at(int index) const;  // data accessor with type conversion to std::string, TODO
  T at(int index) const { return data_[index]; };  // data accessor, read-only
  T& at(int index) { return data_[index]; };  // data accessor, read-and-write
  int get_min_display_width() const;
  std::string get_name() const { return name_; }
  void set_name(std::string name) { name_ = name; }
  int get_size() const { return size_; }
  int get_capacity() const { return capacity_; }
 private:
  std::ostream& operator<<(std::ostream& os) const;  // this is weird, so it is made private
  T default_value_;
  std::string name_ = kDefaultColumnName;
  int size_ = 0;  // the no. of items in the column
  int capacity_ = 0;  // the capacity of the column, which should be >= size_
  T* data_ = nullptr;  // for the internal storage of the column
};

#include "column-submit.h"

template <typename T>
Column<T>::Column(T default_value, int size, int capacity, std::string name)
    : default_value_(default_value), name_(name),
      size_(0), capacity_((capacity < size)? size : capacity) {
  data_ = new T[capacity_];
  expand_size(size);
}

template <typename T>
Column<T>::Column(T default_value, int size, const T* data, std::string name)
    : Column(default_value, 0, size, name) {
  for (int i = 0; i < size; i++) {
    data_[i] = data[i];
  }
  size_ = size;
}

template <typename T>
Column<T>::Column(const Column<T>& other) 
    : Column(other.default_value_, 0, other.capacity_, other.name_) {
  for (int i = 0; i < other.size_; i++) {
    data_[i] = other.data_[i];
  }
  size_ = other.size_;
}

template <typename T>
Column<T>::~Column() {
  if (data_ != nullptr) {
    delete[] data_;
  }
}

#include <sstream>
#include <iomanip>

template <typename T>
int Column<T>::get_min_display_width() const {
  int width = 0;
  int name_width = name_.length() + 2;  // center the column name in the display, 
                                        // and keep some space (at least 1-character width) with the borders on both sides
  int max_width = kMinDisplayWidth;
  std::stringstream ss;
  max_width = (name_width > max_width)? name_width : max_width;
  for (int i = 0; i < size_; i++) {
    ss << data_[i];  // convert the item to a string so that we can check the minimum width needed to display the column
                     // you are not allowed to use this method for as_string_at()
    width = ss.str().length() + 2;
    ss.str("");
    max_width = (width > max_width)? width : max_width;
  }
  if ((max_width % 2) != (name_width % 2)) {
    ++max_width;  // make the column name really aligned to the center of the column
  }
  return max_width;
}

template <typename T>
std::ostream& Column<T>::operator<<(std::ostream& os) const {
  int display_width = get_min_display_width();
  int left_fill = (display_width + name_.length()) / 2;
  int right_pad = display_width - left_fill;
  os << std::boolalpha;
  os << '+' << std::setfill('-') << std::setw(display_width+1) << '+' << std::setfill(' ') << std::endl;
  os << '|' << std::setw(left_fill) << name_ << std::setw(right_pad+1) << '|' << std::endl;
  os << '+' << std::setfill('-') << std::setw(display_width+1) << '+' << std::setfill(' ') << std::endl;
  for (int i = 0; i < size_; i++) {
    os << '|' << std::setw(display_width-1) << data_[i] << " |" << std::endl;
  }
  os << '+' << std::setfill('-') << std::setw(display_width+1) << '+' << std::setfill(' ') << std::endl;
  os << size_ << " items in set (capacity: " << capacity_ << ")" << std::endl;
  os << std::noboolalpha;
  return os;
}

#endif  // COLUMN_H_
