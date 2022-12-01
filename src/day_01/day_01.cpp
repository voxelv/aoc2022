#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "aoc.h"

using namespace std;

int main() {
  auto lines = aoc::get_lines("input/input.txt");

  vector<uint32_t> elf_calories;
  uint32_t calories{};
  for(auto& l : lines){
    if(l.length() == 0){
      elf_calories.push_back(calories);
      calories = 0;
    }
    else{
      calories += stoi(l);
    }
  }

  cout << "PART 1: Max calories: " << *max_element(elf_calories.begin(), elf_calories.end()) << endl;

  sort(elf_calories.begin(), elf_calories.end());

  cout << "PART 2: Top 3 calorie sum: " << reduce(elf_calories.end() - 3, elf_calories.end()) << endl;


  return 0;
}
