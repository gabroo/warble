#include <unordered_map>

class KeyValueStore {
 public:
  int put(const std::string&, const std::string&);
  int get(const std::string&);
  int remove(const std::string&);
 private:
  std::unordered_map<std::string, std::vector<std::string> > map_;
};
