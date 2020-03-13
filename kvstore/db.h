#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

// Interface that represents a database with put, get, and remove functionality.
// Used for KVStoreClient as well as testing (see tests/funcs.cc)
class Database {
 public:
  virtual bool put(std::string, std::string) = 0;
  virtual std::optional<std::vector<std::string>> get(std::string) = 0;
  virtual bool remove(std::string) = 0;
};

#endif  // ! DATABASE_H