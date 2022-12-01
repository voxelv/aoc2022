//
// Created by slippy on 2022-12-01.
//

#include "aoc.h"

namespace aoc {

std::vector<std::string> get_lines(const std::string& input_file) {
  std::vector<std::string>result{};
  auto in_filestream = std::ifstream(input_file);
  if(!in_filestream){
    std::cout << "Error opening input file \"" << input_file << "\"!" << std::endl;
  }
  else {
    std::string line;
    while (getline(in_filestream, line)) {
      result.push_back(line);
    }
  }
  return(result);
}

} // aoc