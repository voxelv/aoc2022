//
// Created by slippy on 2022-12-01.
//

#include <span>
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

void tokenize_on_delim(const std::string& input, const std::string& delimiter, std::vector<std::string>& tokens_out) {
  size_t start;
  size_t end{};

  while((start=input.find_first_not_of(delimiter, end)) != std::string::npos){
    end = input.find(delimiter, start);
    tokens_out.push_back(input.substr(start, end - start));
  }
}


} // aoc