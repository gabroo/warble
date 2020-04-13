/*
  Sajeev Saluja
  @gabroo
  kvstore/store.cc

  Basic key value store with the following API:
    `put(key, value)` associates `value` with `key` in the store
    `get(key)` returns stream of values associated with `key`
    `remove(key)` removes all values associated with `key`

  TODO
    - make thread safe
    - modify keys to include namespaces (ie, bitstrings)
*/

#include "store.h"

bool KVStore::put(const std::string &key, const std::string &value) {
  if (map_.find(key) == map_.end()) {
    map_[key].push_back(value);
  } else {
    std::vector<std::string> vals = map_[key];
    auto find = std::find(vals.begin(), vals.end(), value);
    if (find != vals.end()) {
      return false;
    } else {
      map_[key].push_back(value);
    }
  }
  return true;
}

std::optional<std::vector<std::string>> KVStore::get(const std::string &key) {
  if (map_.find(key) != map_.end()) {
    return map_[key];
  } else {
    return std::nullopt;
  }
}

bool KVStore::remove(const std::string &key) {
  if (map_.find(key) == map_.end()) {
    return false;  // could not find key in map
  } else {
    map_.erase(key);
    return true;
  }
}

void KVStore::read(const std::string &file) {
  std::cout << "reading" << std::endl;
  std::ifstream fs(file);
  if (fs.is_open()) {
    std::string key;
    while (std::getline(fs, key)) {
      std::cout << key << std::endl;
      size_t s;
      fs >> s;
      std::vector<std::string> vals;
      std::string val;
      while (s) {
        std::getline(fs, val);
        vals.push_back(val);
        s--;
      }
      map_[key] = vals;
    }
  } else {
    std::cout << "can't open file" << std::endl;
  }
}

void KVStore::dump(const std::string &file) {
  std::cout << "dumping" << std::endl;
  std::ofstream fs;
  fs.open(file);
  std::unordered_map<std::string, std::vector<std::string>>::iterator itr;
  for (itr = map_.begin(); itr != map_.end(); ++itr) {
    std::string key = itr->first;
    std::vector<std::string> vals = itr->second;
    fs << key << std::endl;
    fs << vals.size() << std::endl;
    for (std::string s : vals) {
      fs << s << std::endl;
    }
  }
  fs.close();
}
