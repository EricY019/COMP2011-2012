// test-index.cpp

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
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 75, "Last Week (1)");
    test_basic_array_indexing_read(a);
  }
  if (case_no == 2 || case_no == -1) {
    print_test_case_number(2);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_songs + 75, "Song (2)");
    test_basic_array_indexing_read(a);
  }
  if (case_no == 3 || case_no == -1) {
    print_test_case_number(3);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 75, "Last Week (3)");
    test_negative_indexing_read(a);
  }
  if (case_no == 4 || case_no == -1) {
    print_test_case_number(4);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_songs + 75, "Song (4)");
    test_negative_indexing_read(a);
  }
  if (case_no == 5 || case_no == -1) {
    print_test_case_number(5);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 75, "Last Week (5)");
    test_basic_array_indexing_write(a);
  }
  if (case_no == 6 || case_no == -1) {
    print_test_case_number(6);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_songs + 75, "Song (6)");
    test_basic_array_indexing_write(a);
  }
  if (case_no == 7 || case_no == -1) {
    print_test_case_number(7);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_weeks_on_chart + 75, "Weeks on Chart (7)");
    test_boolean_indexing(a, a < 10);
  }
  if (case_no == 8 || case_no == -1) {
    print_test_case_number(8);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_artists + 75, "Artist (8)");
    test_boolean_indexing(a, a < "Justin Bieber Featuring Dominic Fike");
  }
  if (case_no == 9 || case_no == -1) {
    print_test_case_number(9);
    Column<bool> a = test_capacity_expansion<bool>(false, 10, 15, -1, billboard_100_awards + 75, "Awards (9)");
    test_boolean_indexing(a, a < true);
  }
  if (case_no == 10 || case_no == -1) {
    print_test_case_number(10);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 20, -1, -1, billboard_100_artists + 75, "Artist (10)", false);
    Column<bool> b = test_capacity_expansion<bool>(false, 20, -1, -1, billboard_100_awards + 75, "Awards (10)", false);
    Column<int> c = test_capacity_expansion<int>(false, 20, -1, -1, billboard_100_weeks_on_chart + 75, "Weeks on Chart (10)", false);
    test_boolean_indexing(a, (a < "Justin Bieber Featuring Dominic Fike") && (b == true) && !(c < 2));
  }
  if (case_no == 11 || case_no == -1) {
    print_test_case_number(11);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_weeks_on_chart + 75, "Weeks on Chart (7)");
    test_integer_indexing_with_conversion_to_string(a);
  }
  if (case_no == 12 || case_no == -1) {
    print_test_case_number(12);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_artists + 75, "Artist (8)");
    test_integer_indexing_with_conversion_to_string(a);
  }
  if (case_no == 13 || case_no == -1) {
    print_test_case_number(13);
    Column<bool> a = test_capacity_expansion<bool>(false, 10, 15, -1, billboard_100_awards + 75, "Awards (9)");
    test_integer_indexing_with_conversion_to_string(a);
  }
}
