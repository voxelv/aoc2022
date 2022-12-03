//
// Created by slippy on 2022-12-02.
//
#include <map>
#include <algorithm>
#include <numeric>
#include "aoc.h"

enum Shape{
  ROCK,
  PAPER,
  SCISSORS,

  SHAPE_COUNT
};

enum Win{
  WIN,
  LOSE,
  DRAW,

  WIN_TYPE_COUNT
};

using namespace std;

uint32_t part1_calculate_score(string line){
  uint32_t score{};

  const map<char, Shape> lut = {{'A', ROCK}, {'B', PAPER}, {'C', SCISSORS},
                                {'X', ROCK}, {'Y', PAPER}, {'Z', SCISSORS}};
  Shape them = lut.at(line.at(0));
  Shape mine = lut.at(line.at(2));

  const map<Shape, uint32_t> shape_score = {{ROCK, 1}, {PAPER, 2}, {SCISSORS, 3}};
  score += shape_score.at(mine);

  Win win_lose_draw = (Win)(((mine-them) + 2) % 3);
  switch(win_lose_draw) {
    case WIN:
      score += 6;
      break;
    case LOSE:
      score += 0;
      break;
    case DRAW:
      score += 3;
      break;
    default:
      break;
  }

  return(score);
}

uint32_t part2_calculate_score(string line){
  uint32_t score{};

  const map<char, Shape> lut = {{'A', ROCK}, {'B', PAPER}, {'C', SCISSORS}};
  Shape them = lut.at(line.at(0));

  const map<char, Win> win_lut = {{'X', LOSE}, {'Y', DRAW}, {'Z', WIN}};
  Win desired_outcome = win_lut.at(line.at(2));

  Shape play_shape{};

  switch(desired_outcome){
    case LOSE:
      switch(them){
        case ROCK:
          play_shape = SCISSORS;
          break;
        case PAPER:
          play_shape = ROCK;
          break;
        case SCISSORS:
          play_shape = PAPER;
          break;
      }
      score += 0;
      break;
    case DRAW:
      play_shape = them;
      score += 3;
      break;
    case WIN:
      switch(them){
        case ROCK:
          play_shape = PAPER;
          break;
        case PAPER:
          play_shape = SCISSORS;
          break;
        case SCISSORS:
          play_shape = ROCK;
          break;
      }
      score += 6;
      break;
    default:
      break;
  }

  switch(play_shape){
    case ROCK:
      score += 1;
      break;
    case PAPER:
      score += 2;
      break;
    case SCISSORS:
      score += 3;
      break;
  }

  return(score);
}

int main() {
  auto lines = aoc::get_lines("i");

  uint32_t part1_score{};
  for(auto& line : lines){
    part1_score += part1_calculate_score(line);
  }
  cout << "Part 1: " << part1_score << endl;

  uint32_t part2_score{};
  for(auto& line : lines){
    part2_score += part2_calculate_score(line);
  }
  cout << "Part 2: " << part2_score << endl;

  return EXIT_SUCCESS;
}