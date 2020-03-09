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

using google::protobuf::Message,
      grpc::CreateChannel,
      grpc::InsecureChannelCredentials;

class WarbleFuncManager {
 public:
  WarbleFuncManager(std::string target) : db_(CreateChannel(target, InsecureChannelCredentials())) {};
  bool execute(std::string, Message*, Message*); // executes a function given a tag
 private:
  // warble functions
  bool RegisterUser(Message*, Message*);
  bool Warble(Message*, Message*);
  bool Follow(Message*, Message*);
  bool Read(Message*, Message*);
  bool Profile(Message*, Message*);
  KVStoreClient db_;
};

#endif // !FUNCTIONS_H