//
// Created by slippy on 2022-12-02.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "aoc.h"

void tokenize_on_delim(const std::string& input, const std::string& delimiter, std::vector<std::string>& tokens_out);

void tokenize_on_delim(const std::string& input, const std::string& delimiter, std::vector<std::string>& tokens_out) {
  size_t start;
  size_t end{};

  while((start=input.find_first_not_of(delimiter, end)) != std::string::npos){
    end = input.find(delimiter, start);
    tokens_out.push_back(input.substr(start, end - start));
  }
}

struct ElfPair {
  std::vector<std::vector<uint32_t>> elf_ranges;

  explicit ElfPair(const std::string& input) {
    std::vector<std::string> tokens{};
    tokenize_on_delim(input, ",", tokens);
    for(const auto& token : tokens) {
      std::vector<std::string> elf_range_strings{};
      std::vector<uint32_t> elf_range;
      tokenize_on_delim(token, "-", elf_range_strings);
      for(const auto& elf_range_string : elf_range_strings) {
        elf_range.push_back(std::stoi(elf_range_string));
      }
      elf_ranges.push_back(elf_range);
    }
  }

  [[nodiscard]] uint32_t get_elf_min(size_t elf_index) const {
    return(elf_ranges.at(elf_index).at(0));
  }

  [[nodiscard]] uint32_t get_elf_max(size_t elf_index) const {
    return(elf_ranges.at(elf_index).at(1));
  }
};


int main() {
  auto lines = aoc::get_lines("i");

  std::vector<ElfPair> elf_pairs{};
  for(const auto& line : lines) {
    elf_pairs.emplace_back(ElfPair{line});
  }

  uint32_t fully_contained_count{};
  for(const auto& elf_pair : elf_pairs) {
    if(elf_pair.get_elf_min(0) <= elf_pair.get_elf_min(1) && elf_pair.get_elf_max(0) >= elf_pair.get_elf_max(1)) {
      // elf 1 is contained in elf 0
      fully_contained_count++;
    }
    else if(elf_pair.get_elf_min(1) <= elf_pair.get_elf_min(0) && elf_pair.get_elf_max(1) >= elf_pair.get_elf_max(0)) {
      // elf 0 is contained in elf 1
      fully_contained_count++;
    }
  }
  std::cout << "Part 1: fully contained count: " << fully_contained_count << std::endl;

  uint32_t overlapping_count{};
  for(const auto& elf_pair : elf_pairs) {
    if(elf_pair.get_elf_min(0) < elf_pair.get_elf_min(1) && elf_pair.get_elf_max(0) < elf_pair.get_elf_min(1)) {
      // not overlapping
    } else if(elf_pair.get_elf_min(0) > elf_pair.get_elf_max(1) && elf_pair.get_elf_max(0) > elf_pair.get_elf_max(1)) {
      // not overlapping
    } else {
      // overlapping
      overlapping_count++;
    }
  }
  std:: cout << "Part 2: overlapping count: " << overlapping_count << std::endl;

  return EXIT_SUCCESS;
}