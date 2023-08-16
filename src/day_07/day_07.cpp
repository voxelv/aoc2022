//
// Created by slippy on 2023-08-16.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "aoc.h"
#include "day_07.h"

#define PACKET_MARKER_SIZE (4)
#define MESSAGE_MARKER_SIZE (14)

using namespace std;

int Directory::get_total_size() const{
  int result = 0;
  for(const auto& dir : directories) {
    result += dir.get_total_size();
  }
  for(const auto& file : files) {
    result += file.size;
  }
  return(result);
}
vector<Directory> Directory::get_all_dirs() const {
  vector<Directory> result{};

  for(auto& dir : directories) {
    vector<Directory> dirs = dir.get_all_dirs();
    result.insert(result.end(), dirs.begin(), dirs.end());
  }

  return(result);
}

int main() {
  auto lines = aoc::get_lines("i");

  Directory root{};

  Directory *current_dir = &root;
  bool listing = false;
  vector<Directory *> path_stack{};
  for(const auto& line : lines) {
    if(listing) {
      if(line.starts_with("dir")) {
        stringstream s{line.substr(4, line.length())};
        string name{};
        s >> name;
        Directory dir{current_dir->path, name};
        current_dir->directories.push_back(dir);
      }
      else if(line.starts_with("$")){
        listing = false;
      }
      else {
        int size{};
        string name{};
        stringstream s{line};
        s >> size;
        s >> name;
        File new_file{name, size};
        current_dir->files.push_back(new_file);
      }
    }

    if(line.starts_with("$ cd ..")) {
      path_stack.pop_back();
    }
    else if(line.starts_with("$ cd")) {
      stringstream s{line.substr(5, line.length())};
      string name{};
      s >> name;
      for(auto& dir : current_dir->directories) {
        if(dir.name == name) {
          current_dir = &dir;
          break;
        }
      }
      path_stack.push_back(name);
    }
    else if(line.starts_with("$ ls")) {
      listing = true;
    }
  }

  vector<Directory> all_dirs{root.get_all_dirs()};
  for(const auto& dir : all_dirs) {
    int size = dir.get_total_size();
    if(size <= 100000) {
      cout << dir.name << endl;
    }
  }

  return EXIT_SUCCESS;
}