// table.h

#ifndef TABLE_H_
#define TABLE_H_

#include "column.h"

#include <string>
#include <iostream>

class Table {
 public:
  Table(int num_int_columns, const Column<int> int_columns[],
        int num_str_columns, const Column<std::string> str_columns[],
        int num_bool_columns, const Column<bool> bool_columns[]);
  ~Table();
  // an interface to get a column view
  template <typename T>
  const Column<T>* get_column_view(std::string name) const;  // TODO
  // an interface to the private version of update_at
  template<class T>
  void update_at(std::string name, int index, T value);  // TODO
  // check compatibility for all data types
  bool is_compatible_with(const Table& other) const;
  // append records for all data types
  void append_records(const Table& other);
  // append records for all data types
  const Table& operator+=(const Table& other);
  // print table
  std::ostream& operator<<(std::ostream& os) const;
  int get_num_columns() const { return num_int_columns_ + num_string_columns_ + num_bool_columns_; }
  int get_num_records() const { return num_records_; } 
 private:
  // copy columns for a certain data type
  template <typename T>
  void copy_columns(int source_num_columns, const Column<T>* source,
                    int& target_num_columns, Column<T>*& target);
  // delete columns for a certain data type
  template <typename T>
  void delete_columns(Column<T>*& columns);
  // append records for a certain data type
  template <typename T>
  void append_records(const Table& other, int& num_columns, Column<T>* columns);  // TODO
  // get a column for a certain data type, const
  template <typename T>
  const Column<T>* get_column(int num_columns, Column<T>* columns, std::string name) const;  // const, e.g. for obtaining a column view
  // get a column for a certain data type, non-const
  template <typename T>
  Column<T>* get_column(int num_columns, Column<T>* columns, std::string name); // overloaded for non-const, e.g. for editing a cell value
  // update an entry of a certain column for a certain data type
  template<class T>
  void update_at(int index, T value, int num_columns,
                 Column<T>* columns, std::string name);
  // check compatiblity of two sets of columns for a certain data type
  template <typename T>
  bool is_compatible_with(int source_num_columns, const Column<T>* source,
                          int target_num_columns, const Column<T>* target) const;
  // visualization
  template <typename T>
  std::ostream& output_columns(std::ostream& os, int num_columns, const Column<T>* columns) const;
  std::ostream& output_sep_line(std::ostream& os, int num_columns, const int* display_width) const; 
  int num_int_columns_ = 0;
  int num_string_columns_ = 0;
  int num_bool_columns_ = 0;
  int num_records_ = 0;
  Column<int>* int_columns_ = nullptr;
  Column<std::string>* string_columns_ = nullptr;
  Column<bool>* bool_columns_ = nullptr;
};

#include "table-submit.h"

template <typename T>
void Table::copy_columns(int source_num_columns, const Column<T>* source,
                         int& target_num_columns, Column<T>*& target) {
  if (target != nullptr) {
    delete_columns<T>(target);
  }
  target_num_columns = source_num_columns;
  if (target_num_columns > 0) {
    target = new Column<T>[target_num_columns];
    int num_records = source[0].get_size();
    for (int i = 0; i < target_num_columns; i++) {
      if (num_records != source[i].get_size()) {
        std::cerr << "! WARNING: sizes of columns do not agree with each other" << std::endl;
      }
      target[i] = Column<T>(source[i]);
    }
  }
}

template <typename T>
void Table::delete_columns(Column<T>*& columns) {
  delete[] columns;
  columns = nullptr;
}

template <typename T>
bool Table::is_compatible_with(int source_num_columns, const Column<T>* source,
                               int target_num_columns, const Column<T>* target) const {
  if (source_num_columns != target_num_columns) {
    return false;
  }
  int num_matches = 0;
  for (int i = 0; i < source_num_columns; i++) {
    for (int j = 0; j < target_num_columns; j++) {
      num_matches += (source[i].get_name() == target[j].get_name());
    }
  }
  return target_num_columns == num_matches;
}

template <typename T>
const Column<T>* Table::get_column(int num_columns, Column<T>* columns, std::string name) const {
  for (int i = 0; i < num_columns; i++) {
    if (columns[i].get_name() == name)
      return &(columns[i]);
  }
  return nullptr;
}

template <typename T>
Column<T>* Table::get_column(int num_columns, Column<T>* columns, std::string name) {
  for (int i = 0; i < num_columns; i++) {
    if (columns[i].get_name() == name)
      return &(columns[i]);
  }
  return nullptr;
}

template<class T>
void Table::update_at(int index, T value, int num_columns, Column<T>* columns, std::string name) {
  get_column(num_columns, columns, name)->operator[](index) = value;
}

template <typename T>
std::ostream& Table::output_columns(std::ostream& os, int num_columns, const Column<T>* columns) const {
  // check the comments in the Column class template
  if (num_columns <= 0) {
    return os;
  }
  int* display_widths = new int[num_columns];
  for (int i = 0; i < num_columns; i++) {
    display_widths[i]  = columns[i].get_min_display_width();
  }
  os << std::boolalpha;
  output_sep_line(os, num_columns, display_widths);
  os << '|';
  int left_fill, right_pad;
  for (int i = 0; i < num_columns; i++) {
    left_fill = (display_widths[i] + columns[i].get_name().length()) / 2;
    right_pad = display_widths[i] - left_fill;
    os << std::setw(left_fill) << columns[i].get_name() << std::setw(right_pad+1) << '|';
  }
  os << std::endl;
  output_sep_line(os, num_columns, display_widths);
  for (int i = 0; i < num_records_; i++) {
    os << '|';
    for (int j = 0; j < num_columns; j++) {
      os << std::setw(display_widths[j]-1) << columns[j].at(i) << " |";
    }
    os << std::endl;
  }
  output_sep_line(os, num_columns, display_widths);
  os << std::noboolalpha;
  delete[] display_widths;
  return os;
}

#endif  // TABLE_H_
