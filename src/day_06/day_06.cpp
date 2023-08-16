//
// Created by slippy on 2022-12-02.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "aoc.h"

#define PACKET_MARKER_SIZE (4)
#define MESSAGE_MARKER_SIZE (14)

using namespace std;

size_t marker_position(int marker_size, const string &datastream) {
  size_t position = 3;
  for(; position < datastream.size(); position++) {
    array<bool, 26>found{};
    found[datastream.at(position) - 'a'] = true;
    bool is_marker = true;
    for(size_t j = 1; j < marker_size; j++) {
      size_t idx = position - j;
      if(found[datastream.at(idx) - 'a']) {
        is_marker = false;
        break;
      }
      else {
        found[datastream.at(idx) - 'a'] = true;
      }
    }

    if(is_marker) {
      break;
    }
  }
  return position + 1;
}


int main() {
  auto lines = aoc::get_lines("i");
  auto& datastream = lines.at(0);

  cout << "PACKET MARKER: " << marker_position(PACKET_MARKER_SIZE, datastream) << endl;
  cout << "MESSAGE MARKER: " << marker_position(MESSAGE_MARKER_SIZE, datastream) << endl;

  return EXIT_SUCCESS;
}