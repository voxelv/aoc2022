//
// Created by slippy on 2022-12-02.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "aoc.h"


using namespace std;


struct Stacks {
  map<uint32_t, vector<char>> stacks;
  size_t stacks_max_key;


  Stacks() : stacks_max_key{} {};

  void add_line(string line) {
    char prev_char = line.at(0);
    uint32_t prev_stack{};
    for(const auto& c : line) {
      if(c == ']') {
        if(!stacks.contains(prev_stack)) {
          stacks.insert_or_assign(prev_stack, vector<char>());
        }
        stacks.at(prev_stack).emplace_back(prev_char);

        if(prev_stack > stacks_max_key) {
          stacks_max_key = prev_stack;
        }
      }
      prev_char = c;
      prev_stack++;
    }
  }

  void compile_stacks() {
    uint32_t count{};
    for(uint32_t i{}; i <= stacks_max_key; i++) {
      if(stacks.contains(i)) {
        reverse(stacks.at(i).begin(), stacks.at(i).end());
        stacks.insert_or_assign(count, stacks.at(i));
        stacks.erase(i);
        count++;
      }
    }
    stacks_max_key = count - 1;
  }

  void part1_move(uint32_t from_stack, uint32_t to_stack) {
    auto crate = stacks.at(from_stack - 1).back();
    stacks.at(from_stack - 1).pop_back();
    stacks.at(to_stack - 1).push_back(crate);
  }

  void part2_move(uint32_t num_to_move, uint32_t from_stack, uint32_t to_stack) {
//    move(stacks.at(from_stack-1).end() - static_cast<int>(num_to_move), stacks.at(from_stack-1).end(), stacks.at(to_stack-1).end());
    auto& v2 = stacks.at(to_stack-1);
    auto& v1 = stacks.at(from_stack-1);
    v2.insert(v2.end(), make_move_iterator(v1.end() - static_cast<int>(num_to_move)), make_move_iterator(v1.end()));
    v1.erase(v1.end() - static_cast<int>(num_to_move), v1.end());
  }

};

struct Movement {
  uint32_t num_to_move;
  uint32_t stack_to_move_from;
  uint32_t stack_to_move_to;

  explicit Movement(const string& line) {
    vector<string> tokens;
    aoc::tokenize_on_delim(line, " ", tokens);

    num_to_move = stoi(tokens.at(1));
    stack_to_move_from = stoi(tokens.at(3));
    stack_to_move_to = stoi(tokens.at(5));
  }
};

int main() {
  auto lines = aoc::get_lines("i");

  uint32_t first_empty_line{};
  auto result = find(lines.begin(), lines.end(), string{""});
  if(result != lines.end()) {
    first_empty_line = result - lines.begin();
  }

  Stacks part1_stacks{};
  Stacks part2_stacks{};
  auto crates = span<string>(lines.begin(), first_empty_line - 1);
  for(const auto& crate_line : crates) {
    part1_stacks.add_line(crate_line);
    part2_stacks.add_line(crate_line);
  }
  part1_stacks.compile_stacks();
  part2_stacks.compile_stacks();

  auto first_move_line = first_empty_line + 1;
  auto movements = span<string>(lines.begin() + static_cast<int>(first_move_line),
                                static_cast<size_t>(lines.size() - first_move_line));

  vector<Movement> movement_list;
  for(const auto& line : movements) {
    movement_list.emplace_back(Movement{line});
  }

  // Part 1 Moves
  for(const auto& movement : movement_list) {
    for(uint32_t i{}; i < movement.num_to_move; i++) {
      part1_stacks.part1_move(movement.stack_to_move_from, movement.stack_to_move_to);
    }
  }

  string part1_result{};
  for(uint32_t i{}; i <= part1_stacks.stacks_max_key; i++) {
    const auto& stack = part1_stacks.stacks.at(i);
    part1_result += stack.back();
  }
  cout << "Part 1: stack tops: " << part1_result << endl;

  // Part2 Moves
  for(const auto& movement : movement_list) {
    part2_stacks.part2_move(movement.num_to_move, movement.stack_to_move_from, movement.stack_to_move_to);
  }

  string part2_result{};
  for(uint32_t i{}; i <= part2_stacks.stacks_max_key; i++) {
    const auto& stack = part2_stacks.stacks.at(i);
    part2_result += stack.back();
  }
  cout << "Part 2: stack tops: " << part2_result << endl;

  return EXIT_SUCCESS;
}