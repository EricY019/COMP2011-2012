// test-add-comp.cpp

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
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 25, "Last Week (1)");
    Column<int> b = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_rank + 25, "Rank (1)");
    std::cout << "* Note: Negating the second column, so that the operation becomes a - b" << std::endl;
    for (int i = 0; i < b.get_size(); i++) {
      b.at(i) = -b.at(i);
    }
    test_addition(a, b);
  }
  if (case_no == 2 || case_no == -1) {
    print_test_case_number(2);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_songs + 25, "Song (2)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 10, 10, -1, billboard_100_artists + 25, "Artist (2)");
    std::cout << "* Note: Adding a dash after each item of a" << std::endl;
    for (int i = 0; i < a.get_size(); i++) {
      a.at(i) = a.at(i) + " - ";
    }
    test_addition(a, b);
  }
  if (case_no == 3 || case_no == -1) {
    print_test_case_number(3);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_last_week + 85, "Rank Increase (3)");
    Column<int> b = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_rank + 85, "Rank (3)");
    std::cout << "* Note: Negating the second column, so that the operation becomes a - b" << std::endl;
    for (int i = 0; i < b.get_size(); i++) {
      b.at(i) = -b.at(i);
    }
    test_addition_assignment(a, b);
  }
  if (case_no == 4 || case_no == -1) {
    print_test_case_number(4);
    Column<std::string> a = test_capacity_expansion<std::string>("Hidden", 10, 10, -1, billboard_100_songs + 85, "Song and Artist (4)");
    Column<std::string> b = test_capacity_expansion<std::string>("Hidden", 10, 15, -1, billboard_100_artists + 85, "Artist (4)");
    std::cout << "* Note: Adding a dash after each item of a" << std::endl;
    for (int i = 0; i < a.get_size(); i++) {
      a.at(i) = a.at(i) + " - ";
    }
    test_addition_assignment(a, b);
  }
  if (case_no == 5 || case_no == -1) {
    print_test_case_number(5);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week, "Last Week (5)");
    Column<int> b = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_rank, "Rank (5)");
    test_equality(a, b);
  }
  if (case_no == 6 || case_no == -1) {
    print_test_case_number(6);
    Column<std::string> a = test_capacity_expansion<std::string>("Unknown", 10, 10, -1, billboard_100_artists, "Artist (6.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Unknown", 10, 15, -1, billboard_100_artists, "Artist (6.2)");
    test_equality(a, b);
  }
  if (case_no == 7 || case_no == -1) {
    print_test_case_number(7);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 90, "Last Week (7)");
    test_equality(a, -1);
  }
  if (case_no == 8 || case_no == -1) {
    print_test_case_number(8);
    Column<std::string> a = test_capacity_expansion<std::string>("Unknown", 10, 10, -1, billboard_100_artists + 75, "Artist (8)");
    test_equality(a, std::string("Justin Bieber"));
  }
  if (case_no == 9 || case_no == -1) {
    print_test_case_number(9);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week, "Last Week (9)");
    Column<int> b = test_capacity_expansion<int>(-1, 10, 15, -1, billboard_100_rank, "Rank (9)");
    test_less_than(a, b);
  }
  if (case_no == 10 || case_no == -1) {
    print_test_case_number(10);
    Column<std::string> a = test_capacity_expansion<std::string>("Unknown", 10, 10, -1, billboard_100_artists, "Artist (10.1)");
    Column<std::string> b = test_capacity_expansion<std::string>("Unknown", 10, 15, -1, billboard_100_artists + 20, "Artist (10.2)");
    test_less_than(a, b);
  }
  if (case_no == 11 || case_no == -1) {
    print_test_case_number(11);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 90, "Last Week (11)");
    test_less_than(a, -1);
  }
  if (case_no == 12 || case_no == -1) {
    print_test_case_number(12);
    Column<std::string> a = test_capacity_expansion<std::string>("Unknown", 10, 10, -1, billboard_100_artists + 75, "Artist (12)");
    test_less_than(a, std::string("Justin Bieber Featuring Dominic Fike"));
  }
  if (case_no == 13 || case_no == -1) {
    print_test_case_number(13);
    Column<bool> a = test_capacity_expansion<bool>(false, 10, 15, -1, billboard_100_awards + 55, "Awards (13)");
    test_negate(a);
  }
  if (case_no == 14 || case_no == -1) {
    print_test_case_number(14);
    Column<int> a = test_capacity_expansion<int>(-1, 10, 10, -1, billboard_100_last_week + 40, "Last Week (14)");
    test_logical_and(a < 40, !(a == -1));
  }
}
