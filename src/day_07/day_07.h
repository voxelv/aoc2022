//
// Created by slippy on 2023-08-16.
//

#ifndef ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_
#define ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_

using namespace std;

class File {
public:
  string name;
  int size;
};

class Directory {
public:
  vector<string> path{};
  string name{};
  vector<Directory> directories{};
  vector<File> files{};

  int get_total_size() const;
  vector<Directory> get_all_dirs() const;
};

#endif // ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_
