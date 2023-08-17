//
// Created by slippy on 2023-08-16.
//

#ifndef ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_
#define ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_

using namespace std;

struct File {
  string name;
  int size;
};

class Directory {
public:
  string name{};
  vector<string> path{};

private:
  vector<Directory *> directories{};
  vector<File *> files{};

public:
  Directory(string dirname, const vector<string>& dirpath);
  void add_file(string name, int size);
  void add_directory(string dirname, const vector<string>& dirpath);
  Directory * get_directory(string dirname) const;
  int get_total_size() const;
  vector<Directory const *> get_all_dirs() const;

  ~Directory();
};

#endif // ADVENT_OF_CODE_2022_SRC_DAY_07_DAY_07_H_
