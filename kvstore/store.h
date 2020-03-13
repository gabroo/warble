/*
  Sajeev Saluja
  @gabroo
  kvstore/store.h

  Backend key value store headers. See kvstore/store.cc for implementation.
*/

#ifndef KVSTORE_H
#define KVSTORE_H

#include <algorithm>
#include <optional>
#include <unordered_map>
#include <vector>

// Backend data structure for storing values in memory, using std::unordered_map.
class KVStore {
 public:
  bool put(const std::string&, const std::string&);
  // Keys that do not have values will return std::nullopt
  std::optional<std::vector<std::string>> get(const std::string&);
  bool remove(const std::string&);

 private:
  std::unordered_map<std::string, std::vector<std::string>> map_;
};

#endif  // !KVSTORE_H