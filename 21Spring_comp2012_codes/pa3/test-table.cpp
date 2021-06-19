// test-table.cpp

#include "column.h"
#include "table.h"
#include "test-utils.h"

#include <string>
#include <iostream>

Table read_billboard(int num_records, int start=0) {
  Column<int> rank = test_capacity_expansion<int>(-1, num_records, -1, -1, billboard_100_rank + start, "Rank");
  Column<int> last_week = test_capacity_expansion<int>(-1, num_records, -1, -1, billboard_100_last_week + start, "Last Week");
  Column<int> peak = test_capacity_expansion<int>(-1, num_records, -1, -1, billboard_100_peak + start, "Peak");
  Column<int> woc = test_capacity_expansion<int>(-1, num_records, -1, -1, billboard_100_weeks_on_chart + start, "Week on Chart");
  Column<std::string> artists = test_capacity_expansion<std::string>("Unknown Artist(s)", num_records, -1, -1, billboard_100_artists + start, "Artists");
  Column<std::string> songs = test_capacity_expansion<std::string>("Unknown Song", num_records, -1, -1, billboard_100_songs + start, "Song");
  Column<bool> awards = test_capacity_expansion<bool>(false, num_records, -1, -1, billboard_100_awards + start, "Awards");
  
  Column<int> int_columns[] = {rank, last_week, peak, woc};
  Column<std::string> string_columns[] = {artists, songs};
  Column<bool> bool_columns[] = {awards};
  Table billboard {4, int_columns, 2, string_columns, 1, bool_columns};
  return billboard;
}

void test_append_table() {
  Table part1 = read_billboard(10, 0);
  Table part2 = read_billboard(10, 10);
  Table part3 = read_billboard(10, 20);
  print_test_name("Append table");
  std::cout << "* Start with Part 1" << std::endl;
  part1 << std::cout;
  std::cout << "* Append Part 2" << std::endl;
  part1 += part2;
  part1 << std::cout;
  std::cout << "* Append Part 3" << std::endl;
  part1 += part3;
  part1 << std::cout;
  std::cout << std::endl;
}

void test_column_view() {
  Table part1 = read_billboard(10, 0);
  print_test_name("Get Column View");
  std::cout << "* Get Rank" << std::endl;
  std::cout << *(part1.get_column_view<int>("Rank"));
  std::cout << "* Get Artists" << std::endl;
  std::cout << *(part1.get_column_view<std::string>("Artists"));
  std::cout << "* Get Awards" << std::endl;
  std::cout << *(part1.get_column_view<bool>("Awards"));
  std::cout << std::endl;
}

void test_update_entries() {
  Table part3 = read_billboard(10, 20);
  print_test_name("Update Entries");
  std::cout << "* Update Rank" << std::endl;
  part3.update_at<int>("Rank", 0, -1);
  std::cout << "* Update Artists" << std::endl;
  part3.update_at<std::string>("Artists", 0, "Test");
  std::cout << "* Update Awards" << std::endl;
  part3.update_at<bool>("Awards", 0, false);
  part3 << std::cout;
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  int case_no = -1;
  if (argc == 2)
    case_no = std::stoi(argv[1]);
  if (case_no == 1 || case_no == -1) {
    print_test_case_number(1);
    test_append_table();
  }
  if (case_no == 2 || case_no == -1) {
    print_test_case_number(2);
    test_column_view();
  }
  if (case_no == 3 || case_no == -1) {
    print_test_case_number(3);
    test_update_entries();
  }
}
