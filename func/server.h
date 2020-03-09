/*
  Sajeev Saluja
  @gabroo
  func/server.h

  Forward declarations for func/server.cc
*/

#ifndef FUNCSERVER_H
#define FUNCSERVER_H

#include <iostream>
#include <grpc++/grpc++.h>
#include "protos/func.grpc.pb.h"
#include "protos/kvstore.grpc.pb.h"
#include "kvstore/client.h"
#include "protos/warble.pb.h"
#include "functions.h"

using warble::RegisterUserRequest,
      warble::RegisterUserReply,
      grpc::protobuf::Message;

using grpc::Status,
      grpc::ServerContext,
      grpc::WriteOptions,
      grpc::ChannelInterface,
      grpc::CreateChannel,
      grpc::InsecureChannelCredentials,
      func::FuncService,
      func::HookRequest,
      func::HookReply,
      func::UnhookRequest,
      func::UnhookReply,
      func::EventRequest,
      func::EventReply,
      kvstore::KeyValueStore;


class FuncServer final : public FuncService::Service {
 public:
  FuncServer(std::string target) : funcs_(target) {};
  Status hook(ServerContext*, const HookRequest*, HookReply*);
  Status unhook(ServerContext*, const UnhookRequest*, UnhookReply*);
  Status event(ServerContext*, const EventRequest*, EventReply*);

 private:
  std::unordered_map<int, std::string> events_;
  WarbleFuncManager funcs_;
};

#endif // !FUNCSERVER_H