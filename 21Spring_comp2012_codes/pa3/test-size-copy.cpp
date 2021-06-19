// test-size-copy.cpp

#include "column.h"
#include "test-utils.h"

#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
  int case_no = -1;
  if (argc == 2)
    case_no = std::stoi(argv[1]);
  if (case_no == 1 || case_no == -1) {
    print_test_case_number(1);
    test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_songs, "Song (1)", false);  // reserve capacity only
  }
  if (case_no == 2 || case_no == -1) {
    print_test_case_number(2);
    test_capacity_expansion<std::string>("Hidden", 10, 20, 15, billboard_100_songs + 10, "Song (2)", false);  // reserve capacity and expand size 1.1 (capacity > size)
  }
  if (case_no == 3 || case_no == -1) {
    print_test_case_number(3);
    test_capacity_expansion<std::string>("Hidden", 10, 15, 15, billboard_100_songs + 20, "Song (3)", false);  // reserve capacity and expand size 1.2 (capacity == size)
  }
  if (case_no == 4 || case_no == -1) {
    print_test_case_number(4);
    test_capacity_expansion<std::string>("Hidden", 10, -1, 15, billboard_100_songs + 30, "Song (4)", false);  // expand size only
  }
  if (case_no == 5 || case_no == -1) {
    print_test_case_number(5);
    test_capacity_expansion<std::string>("Hidden", 10, 15, 20, billboard_100_songs + 40, "Song (5)", false);  // reserve capacity and expand size 2 (capacity < size)
  }
  if (case_no == 6 || case_no == -1) {
    print_test_case_number(6);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 5, 15, -1, billboard_100_songs + 50, "Song (6.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 55, "Song (6.2)");
    test_append(a, b); // append 1.1 (capacity > size)
  }
  if (case_no == 7 || case_no == -1) {
    print_test_case_number(7);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 5, 10, -1, billboard_100_songs + 60, "Song (7.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 65, "Song (7.2)");
    test_append(a, b); // append 1.2 (capacity == size)
  }
  if (case_no == 8 || case_no == -1) {
    print_test_case_number(8);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 70, "Song (8.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 75, "Song (8.2)");
    test_append(a, b); // append 2 (capacity < size)
  }
  if (case_no == 9 || case_no == -1) {
    print_test_case_number(9);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 10, -1, billboard_100_songs + 50, "Song (9.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 55, "Song (9.2)");
    test_copy_assignment(a, b); // copy assignment 1.1 (capacity > size)
  }
  if (case_no == 10 || case_no == -1) {
    print_test_case_number(10);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 60, "Song (10.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 65, "Song (10.2)");
    test_copy_assignment(a, b); // copy assignment 1.2 (capacity == size)
  }
  if (case_no == 11 || case_no == -1) {
    print_test_case_number(11);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 5, 5, -1, billboard_100_songs + 70, "Song (11.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 10, 10, -1, billboard_100_songs + 75, "Song (11.2)");
    test_copy_assignment(a, b); // copy assignment 2 (capacity < size)
  }
}
