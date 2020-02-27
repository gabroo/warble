/*
  Sajeev Saluja
  @gabroo
  kvstore.h
  
  Backend key value store headers. See kvstore.cc for implementation details.
*/
#include <unordered_map>
#include <vector>
#include <optional>

class KVStore {
 public:
  bool put(const std::string&, const std::string&);
  std::optional<std::vector<std::string>> get(const std::string&);
  bool remove(const std::string&);
 private:
  std::unordered_map<std::string, std::vector<std::string>> map_;
};
