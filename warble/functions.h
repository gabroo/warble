/*
  Sajeev Saluja
  @gabroo
  func/functions.h

  Forward declarations for the Warble functions.
  See functions.cc
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <grpc++/grpc++.h>

#include <iostream>
#include <stack>

#include "glog/logging.h"
#include "kvstore/db.h"
#include "protos/func.pb.h"
#include "protos/warble.pb.h"

using google::protobuf::Message, google::protobuf::Any, grpc::CreateChannel,
    grpc::InsecureChannelCredentials, warble::Timestamp,
    warble::RegisterUserRequest, warble::RegisterUserReply,
    warble::WarbleRequest, warble::WarbleReply, warble::FollowRequest,
    warble::FollowReply, warble::ReadRequest, warble::ReadReply,
    warble::ProfileRequest, warble::ProfileReply, func::EventRequest,
    func::EventReply;

bool RegisterUser(Database* db, Any, Any*);
bool Warble(Database* db, Any, Any*);
bool Follow(Database* db, Any, Any*);
bool Read(Database* db, Any, Any*);
bool Profile(Database* db, Any, Any*);

typedef std::function<bool(Database*, Any, Any*)> fn;
static std::unordered_map<std::string, fn> funcs({{"register_user",
                                                   RegisterUser},
                                                  {"warble", Warble},
                                                  {"follow", Follow},
                                                  {"read", Read},
                                                  {"profile", Profile}});

#endif  // !FUNCTIONS_H