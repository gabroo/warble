/*
  Sajeev Saluja
  @gabroo
  func_server.h

  Forward declarations for func_server.cc
*/

#include <iostream>
#include <grpc++/grpc++.h>
#include "protos/func.grpc.pb.h"
#include "protos/kvstore.grpc.pb.h"
#include "kvstore/client.h"

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
  FuncServer() : kvc_(CreateChannel("0.0.0.0:50001", InsecureChannelCredentials())) {};
  Status hook(ServerContext*, const HookRequest*, HookReply*);
  Status unhook(ServerContext*, const UnhookRequest*, UnhookReply*);
  Status event(ServerContext*, const EventRequest*, EventReply*);
 private:
  KVStoreClient kvc_;
};
