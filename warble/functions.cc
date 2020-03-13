#include "functions.h"

bool RegisterUser(const KVStoreClient &db, Any req, Any rep) {
  RegisterUserRequest request;
  req.UnpackTo(&request);
  std::string username = request.username();
  db.put("warble_users", username);
  return true;
}

bool Warble(const KVStoreClient &db, Any req, Any rep) {
  std::cout << "in Warble" << std::endl;
  WarbleRequest request;
  req.UnpackTo(&request);
  std::string username = request.username(),
              text = request.text(),
              parent_id = request.parent_id();
  std::string key("warble_"+username);
  std::string warble_id;
  auto exists = db.get(key);
  if (exists) {
    warble_id = username + (char*)(*exists).size();
  } else {
    warble_id = username + "0";
  }
  db.put(key, warble_id);
  return true;
}

bool Follow(const KVStoreClient &db, Any req, Any rep) {
  return true;
}

bool Read(const KVStoreClient &db, Any req, Any rep) {
  return true;
}

bool Profile(const KVStoreClient &db, Any req, Any rep) {
  return true;
}