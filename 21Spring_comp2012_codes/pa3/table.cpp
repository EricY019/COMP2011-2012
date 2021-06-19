// table.cpp

#include "table.h"
#include <string>

Table::Table(int num_int_columns, const Column<int>* int_columns,
             int num_string_columns, const Column<std::string>* string_columns,
             int num_bool_columns, const Column<bool>* bool_columns) {
  // copy records for each data type
  copy_columns<int>(num_int_columns, int_columns, num_int_columns_, int_columns_);
  copy_columns<std::string>(num_string_columns, string_columns, num_string_columns_, string_columns_);
  copy_columns<bool>(num_bool_columns, bool_columns, num_bool_columns_, bool_columns_);
  if (num_int_columns_ > 0) {
    num_records_ = int_columns_[0].get_size();
  }
  if (num_string_columns_ > 0) {
    int temp_records = string_columns_[0].get_size();
    if (temp_records != num_records_)
      std::cerr << "! WARNING: sizes of columns do not agree with each other" << std::endl;
    num_records_ = (temp_records > num_records_) ? num_records_ : temp_records;
  }
  if (num_bool_columns_ > 0) {
    int temp_records = bool_columns_[0].get_size();
    if (temp_records != num_records_)
      std::cerr << "! WARNING: sizes of columns do not agree with each other" << std::endl;
    num_records_ = (temp_records > num_records_) ? num_records_ : temp_records;
  }
}

Table::~Table() {
  // delete records for each data type
  delete[] int_columns_;
  delete[] string_columns_;
  delete[] bool_columns_;
}

bool Table::is_compatible_with(const Table& other) const {
  if (get_num_columns() != other.get_num_columns())
    return false;
  // check compatibility for each data type
  if (!is_compatible_with<int>(other.num_int_columns_, other.int_columns_, 
                               num_int_columns_, int_columns_))
    return false;
  if (!is_compatible_with<std::string>(other.num_string_columns_, other.string_columns_, 
                                       num_string_columns_, string_columns_))
    return false;
  if (!is_compatible_with<bool>(other.num_bool_columns_, other.bool_columns_, 
                                num_bool_columns_, bool_columns_))
    return false;
  return true;
}

void Table::append_records(const Table& other) {
  if (is_compatible_with(other)) {
    // append records for each data type
    append_records(other, num_int_columns_, int_columns_);
    append_records(other, num_string_columns_, string_columns_);
    append_records(other, num_bool_columns_, bool_columns_);
    num_records_ += other.get_num_records();
  }
}

const Table& Table::operator+=(const Table& other) {
  append_records(other);
  return *this;
}

std::ostream& Table::output_sep_line(std::ostream& os, int num_columns, const int* display_widths) const {
  // this function prints a horizontal line like +--------+ for visualizaing a table
  os << '+';
  os << std::setfill('-');
  for (int i = 0; i < num_columns; i++) {
    os << std::setw(display_widths[i]+1) << '+';
  }
  os << std::setfill(' ');
  os << std::endl;
  return os;
}

std::ostream& Table::operator<<(std::ostream& os) const {
  // this groups columns for the same data type in a sub-table for visualization
  output_columns(os, num_int_columns_, int_columns_) << "(integer columns)" << std::endl;
  output_columns(os, num_string_columns_, string_columns_) << "(string columns)" << std::endl;
  output_columns(os, num_bool_columns_, bool_columns_) << "(boolean columns)" << std::endl;
  os << get_num_records() << " records and " << get_num_columns() << " columns in set" << std::endl;
  return os;
}
