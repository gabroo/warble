/*
  Sajeev Saluja
  @gabroo
  func/functions.h

  Forward declarations for the Warble functions.
  See functions.cc
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <grpc++/grpc++.h>
#include "kvstore/client.h"
#include "protos/warble.pb.h"
#include "protos/func.pb.h"

using google::protobuf::Message,
      google::protobuf::Any,
      grpc::CreateChannel,
      grpc::InsecureChannelCredentials,
      warble::Warble,
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
      warble::ProfileReply,
      func::EventRequest,
      func::EventReply;

bool RegisterUser(const KVStoreClient &db, Any, Any);
bool Warble(const KVStoreClient &db, Any, Any);
bool Follow(const KVStoreClient &db, Any, Any);
bool Read(const KVStoreClient &db, Any, Any);
bool Profile(const KVStoreClient &db, Any, Any);

typedef std::function<bool(const KVStoreClient&, Any, Any)> fn;
static std::unordered_map<std::string, fn> funcs({
  {"register_user", RegisterUser},
  {"warble", Warble},
  {"follow", Follow},
  {"read", Read},
  {"profile", Profile}
});

#endif // !FUNCTIONS_H