//
// Created by slippy on 2022-12-01.
//

#ifndef ADVENT_OF_CODE_2022_LIB_AOC_AOC_H_
#define ADVENT_OF_CODE_2022_LIB_AOC_AOC_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <span>

namespace aoc {

std::vector<std::string> get_lines(const std::string& input_file);

void tokenize_on_delim(const std::string& input, const std::string& delimiter, std::vector<std::string>& tokens_out);

} // aoc

#endif //ADVENT_OF_CODE_2022_LIB_AOC_AOC_H_
