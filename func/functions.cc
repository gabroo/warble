#include "functions.h"

using warble::Warble,
      warble::Timestamp,
      warble::RegisterUserRequest,
      warble::RegisterUserReply,
      warble::WarbleRequest,
      warble::WarbleReply,
      warble::FollowRequest,
      warble::FollowReply,
      warble::ReadRequest,
      warble::ReadReply,
      warble::ProfileRequest,
      warble::ProfileReply;


bool WarbleFuncManager::execute(std::string function, Message* req, Message* rep) {
  if (function.compare("register_user") == 0) {
    return RegisterUser(req, rep);
  }
  return false;
}

bool WarbleFuncManager::RegisterUser(Message* req, Message* rep) {
  std::cout << "in WarbleFuncManager::RegisterUser" << std::endl;
  RegisterUserRequest* request = reinterpret_cast<RegisterUserRequest*>(req);
  std::string username = request->username();
  // put username in db, will override if doesn't exist
  db_.put("warble_users", username);
  return true;
}

bool WarbleFuncManager::Warble(Message* req, Message* rep) {
  WarbleRequest* request = reinterpret_cast<WarbleRequest*>(req);
  std::cout << "in WarbleFuncManager::Warble" << std::endl;
  std::string username = request->username(),
              text = request->text(),
              parent_id = request->parent_id();
  // make a warble under the given username
  std::string key("warble_"+username);
  std::string warble_id;
  auto exists = db_.get(key);
  if (exists) {
    warble_id = username + (char*)(*exists).size();
  } else {
    warble_id = username + "0";
  }
  db_.put(key, warble_id);
  return true;
}

bool WarbleFuncManager::Follow(Message* req, Message* rep) {
  FollowRequest* request = reinterpret_cast<FollowRequest*>(req);
  return true;
}

bool WarbleFuncManager::Read(Message* req, Message* rep) {
  ReadRequest* request = reinterpret_cast<ReadRequest*>(req);
  return true;
}

bool WarbleFuncManager::Profile(Message* req, Message* rep) {
  ProfileRequest* request = reinterpret_cast<ProfileRequest*>(req);
  return true;
}