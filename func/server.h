/*
  Sajeev Saluja
  @gabroo
  func/server.h

  Forward declarations for func/server.cc
*/

#ifndef FUNCSERVER_H
#define FUNCSERVER_H

#include <grpc++/grpc++.h>

#include <iostream>

#include "kvstore/client.h"
#include "protos/func.grpc.pb.h"
#include "protos/kvstore.grpc.pb.h"
#include "protos/warble.pb.h"
#include "warble/functions.h"

using grpc::Status, grpc::ServerContext, grpc::WriteOptions,
    grpc::CreateChannel, grpc::InsecureChannelCredentials, func::FuncService,
    func::HookRequest, func::HookReply, func::UnhookRequest, func::UnhookReply,
    func::EventRequest, func::EventReply, warble::RegisterUserRequest,
    warble::RegisterUserReply, google::protobuf::Message, google::protobuf::Any,
    kvstore::KeyValueStore;

class FuncServer final : public FuncService::Service {
 public:
  FuncServer(std::string target)
      : db_(CreateChannel(target, InsecureChannelCredentials())){};
  Status hook(ServerContext*, const HookRequest*, HookReply*) override;
  Status unhook(ServerContext*, const UnhookRequest*, UnhookReply*) override;
  Status event(ServerContext*, const EventRequest*, EventReply*) override;

 private:
  std::unordered_map<int, std::string> events_;
  KVStoreClient db_;
};

#endif  // !FUNCSERVER_H