#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

class Database {
 public:
  virtual bool put(std::string, std::string) = 0;
  virtual std::optional<std::vector<std::string>> get(std::string) = 0;
  virtual bool remove(std::string) = 0;
};

#endif  // ! DATABASE_H