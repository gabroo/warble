/*
  Sajeev Saluja
  @gabroo
  kvstore.cc

  Basic key value store with the following API:
    `put(key, value)` associates `value` with `key` in the store
    `get(key)` returns stream of values associated with `key`
    `remove(key)` removes all values associated with `key`

  TODO
    - make thread safe
    - modify keys to include namespaces (ie, bitstrings)
*/

#include "kvstore.h"

int KVStore::put(const std::string &key, const std::string &value) {
  map_[key].push_back(value);
  return 0;
}

std::vector<std::string> KVStore::get(const std::string &key) {
  if (map_.find(key) != map_.end()) {
    return map_[key];
  } else {
    return std::vector<std::string>();
  }
}

int KVStore::remove(const std::string &key) {
  map_.erase(key);
  return 0;
}
