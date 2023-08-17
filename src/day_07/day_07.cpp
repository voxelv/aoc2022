//
// Created by slippy on 2023-08-16.
//
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <utility>
#include "aoc.h"
#include "day_07.h"

#define PACKET_MARKER_SIZE (4)
#define MESSAGE_MARKER_SIZE (14)

using namespace std;

Directory::Directory(string dirname, const vector<string>& dirpath) {
  name = std::move(dirname);
  for(const auto& s : dirpath) {
    path.push_back(s);
  }
}

Directory::~Directory() {
  for(auto dir : directories) {
    delete dir;
  }
  for(auto file : files) {
    delete file;
  }
}

int Directory::get_total_size() const{
  int result = 0;
  for(const auto& dir : directories) {
    result += dir->get_total_size();
  }
  for(const auto& file : files) {
    result += file->size;
  }
  return(result);
}
vector<Directory const *> Directory::get_all_dirs() const {
  vector<Directory const *> result{};
  result.push_back(this);

  for(auto& dir : directories) {
    auto dirs = dir->get_all_dirs();
    result.insert(result.end(), dirs.begin(), dirs.end());
  }

  return(result);
}

void Directory::add_file(string filename, int size) {
  File *new_file = new File{std::move(filename), size};
  files.push_back(new_file);
}

void Directory::add_directory(string dirname, const vector<string>& dirpath) {
  auto new_dir = new Directory{std::move(dirname), dirpath};
  directories.push_back(new_dir);
}
Directory *Directory::get_directory(string dirname) const {
  Directory *result = nullptr;

  for(const auto& dir : directories) {
    if(dir->name == dirname) {
      result = dir;
      break;
    }
  }

  return result;
}

int main() {
  auto lines = aoc::get_lines("i");

  Directory root{"/", {}};

  Directory *current_dir = &root;
  bool listing = false;
  vector<Directory *> path_stack = {current_dir};
  for(const auto& line : lines) {
    if(listing) {
      if(line.starts_with("dir")) {
        stringstream s{line.substr(4, line.length())};
        string name{};
        s >> name;

        vector<string> path{};
        for(auto p : path_stack) {
          path.push_back(p->name);
        }
        current_dir->add_directory(name, path);
      }
      else if(line.starts_with("$")){
        listing = false;
      }
      else { // File
        int size{};
        string name{};
        stringstream s{line};
        s >> size;
        s >> name;
        current_dir->add_file(name, size);
      }
    }

    if(line.starts_with("$ cd ..")) {
      path_stack.pop_back();
      current_dir = path_stack.back();
    }
    else if(line.starts_with("$ cd")) {
      stringstream s{line.substr(5, line.length())};
      string name{};
      s >> name;

      current_dir = current_dir->get_directory(name);
      if(current_dir == nullptr) {
        current_dir = &root;
      }
      else {
        path_stack.push_back(current_dir);
      }
    }
    else if(line.starts_with("$ ls")) {
      listing = true;
    }
  }

  vector<Directory const *> all_dirs{root.get_all_dirs()};
  int total = 0;
  for(const auto& dir : all_dirs) {
    int size = dir->get_total_size();
    if(size <= 100000) {
      total += size;
    }
  }
  cout << "total of dirs >100K: " << total << endl;

  return EXIT_SUCCESS;
}