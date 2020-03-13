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

// Registers a username that can be later used to login
bool RegisterUser(Database* db, Any, Any*);
// Posts a warble to a given account, returns warble ID
bool Warble(Database* db, Any, Any*);
// Creates a follower/following relationship between two users
bool Follow(Database* db, Any, Any*);
// Reads an entire thread (recursively) from a root warble
bool Read(Database* db, Any, Any*);
// Gets the profile (followers and following) of a user
bool Profile(Database* db, Any, Any*);

// type definition of an arbitrary function that is executed by func
typedef std::function<bool(Database*, Any, Any*)> fn;
static std::unordered_map<std::string, fn> funcs({{"register_user",
                                                   RegisterUser},
                                                  {"warble", Warble},
                                                  {"follow", Follow},
                                                  {"read", Read},
                                                  {"profile", Profile}});
#endif  // !FUNCTIONS_H