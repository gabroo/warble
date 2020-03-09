/*
  Sajeev Saluja
  @gabroo
  kvstore/store.h

  Backend key value store headers. See kvstore/store.cc for implementation.
*/

#ifndef KVSTORE_H
#define KVSTORE_H

#include <unordered_map>
#include <vector>
#include <optional>
#include <algorithm>

class KVStore {
 public:
  bool put(const std::string&, const std::string&);
  std::optional<std::vector<std::string>> get(const std::string&);
  bool remove(const std::string&);
 private:
  std::unordered_map<std::string, std::vector<std::string>> map_;
};

#endif // !KVSTORE_H