//
// Created by slippy on 2023-08-16.
//
#include <algorithm>
#include <map>
#include <numeric>
#include <sstream>
#include <utility>
#include "aoc.h"
#include "day_08.h"

#define PACKET_MARKER_SIZE (4)
#define MESSAGE_MARKER_SIZE (14)

using namespace std;

struct Forest {
  size_t w;
  size_t h;
  uint8_t *data;

  Forest(size_t width, size_t height) : w{width}, h{height} {
    data = new uint8_t[h * w];
  }

  void set(size_t x, size_t y, uint8_t tree) {
    data[y * w + x] = tree;
  }

  uint8_t at(size_t x, size_t y) const {
    return(data[y * w + x]);
  }

  ~Forest() {
    delete[] data;
  }

};

bool is_visible(size_t x, size_t y, Forest& forest) {
  bool result = true;
  size_t i = 0;
  bool visible_n = true, visible_e = true, visible_s = true, visible_w = true;

  // Border trees are visible
  if(x == 0 || y == 0 || x == forest.w - 1 || y == forest.h - 1) {
    return(true);
  }

  uint8_t this_tree = forest.at(x, y);
  for(i = 0; i < forest.w; i++) {
    if(i < x) {
      visible_w &= forest.at(i, y) < this_tree;
    }
    else if(i > x) {
      visible_e &= forest.at(i, y) < this_tree;
    }
  }
  for(i = 0; i < forest.h; i++) {
    if(i < y) {
      visible_n &= forest.at(x, i) < this_tree;
    }
    else if(i > y) {
      visible_s &= forest.at(x, i) < this_tree;
    }
  }

  result = visible_n || visible_e || visible_s || visible_w;
  return(result);
}

uint64_t scenic_score(size_t x, size_t y, Forest& forest) {
  uint64_t result = 0;
  uint64_t n = 0, e = 0, s = 0, w = 0;

  uint8_t this_tree = forest.at(x, y);

  int64_t i = 0;
  for(i = y-1; i >= 0; i--) {
    n++;
    if(forest.at(x, i) >= this_tree) {
      break;
    }
  }

  for(i = y+1; i < forest.h; i++) {
    s++;
    if(forest.at(x, i) >= this_tree) {
      break;
    }
  }

  for(i = x-1; i >= 0; i--) {
    w++;
    if(forest.at(i, y) >= this_tree) {
      break;
    }
  }

  for(i = x+1; i < forest.w; i++) {
    e++;
    if(forest.at(i, y) >= this_tree) {
      break;
    }
  }

  result = n * e * s * w;
  return(result);
}

int main() {
  auto lines = aoc::get_lines("i");

  size_t forest_w = lines.at(0).length();
  size_t forest_h = lines.size();
  size_t i = 0;
  Forest forest(forest_w, forest_h);
  for(i = 0; i < forest_h; i++) {
    size_t j = 0;
    for(j = 0; j < forest_w; j++) {
      const auto& tree_height = lines.at(i).at(j);
      forest.set(j, i, tree_height - '0');
    }
  }

  size_t visible_count = 0;
  uint64_t highest_scenic_score = 0;
  for(i = 0; i < forest_w; i++) {
    size_t j = 0;
    for(j = 0; j < forest_h; j++) {
      if(is_visible(i, j, forest)) {
        visible_count++;
      }
      highest_scenic_score = max(highest_scenic_score, scenic_score(i, j, forest));
    }
  }

  cout << "visible trees: " << visible_count << endl;
  cout << "highest scenic score: " << highest_scenic_score << endl;

  return EXIT_SUCCESS;
}