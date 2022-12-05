//
// Created by slippy on 2022-12-02.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <bitset>
#include "aoc.h"

uint32_t part1_rucksack_priority(std::string sack);
uint32_t get_priority(char item_type);
uint32_t part2_group_of_3_badges_sum(std::vector<std::string>& lines);

int main() {
  auto lines = aoc::get_lines("i");

  uint32_t part1_priority_sum{};
  for(auto& line : lines) {
    part1_priority_sum += part1_rucksack_priority(line);
  }
  std::cout << "Part 1 priority sum: " << part1_priority_sum << std::endl;

  std::cout << "Part 2 badge sum: " << part2_group_of_3_badges_sum(lines) << std::endl;

  return EXIT_SUCCESS;
}

uint32_t part1_rucksack_priority(std::string sack) {
  std::map<char, uint32_t> char_count{};
  for(uint32_t i = 0; i < sack.length(); i++) {
    char c = sack[i];
    if(i < sack.length() / 2) {
      char_count.insert_or_assign(c, char_count.contains(c) ? char_count.at(c) | 0x01 : 0x01);
    }
    else {
      char_count.insert_or_assign(c, char_count.contains(c) ? char_count.at(c) | 0x02 : 0x02);
    }
  }

  char duplicate{};
  for(auto& pair : char_count) {
    if(pair.second == 3) {
      duplicate = pair.first;
    }
  }

  uint32_t priority = get_priority(duplicate);

  return(priority);
}

uint32_t get_priority(char item_type) {
  uint32_t priority{};
  if(isupper(item_type)) {
    priority = item_type - 'A' + 1 + 26;
  }
  else {
    priority = item_type - 'a' + 1;
  }
  return(priority);
}

uint32_t part2_group_of_3_badges_sum(std::vector<std::string>& lines){
  uint32_t badge_priority_sum{};

  uint32_t count{};
  while(count + 1 < lines.size()) {
    std::map<uint32_t, uint64_t> items{};
    for(uint32_t i = 0; i < 3; i++) {
      for(auto& c : lines.at(count + i)) {
        items.insert_or_assign(i, items.contains(i) ? items.at(i) | 1LL << get_priority(c): 1LL << get_priority(c));
        }
      }
    count += 3;

    uint64_t bits= ~static_cast<uint64_t>(0x0);
    for(auto& pair : items) {
      bits &= pair.second;
    }
    for(uint32_t i = 0; i < 64; i++) {
      if((bits >> i) & 1LL) {
        badge_priority_sum += i;
        break;
      }
    }
  }

  return(badge_priority_sum);
}
