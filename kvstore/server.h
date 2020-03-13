/*
  Sajeev Saluja
  @gabroo
  kvstore/server.h

  Forward declarations for kvstore/server.cc
*/

#ifndef KVSERVER_H
#define KVSERVER_H

#include <iostream>
#include <unordered_map>
#include <grpc++/grpc++.h>
#include "protos/kvstore.grpc.pb.h"
#include "store.h"

using grpc::Status,
      grpc::ServerContext,
      grpc::ServerWriter,
      grpc::WriteOptions,
      kvstore::KeyValueStore,
      kvstore::PutRequest,
      kvstore::PutReply,
      kvstore::GetRequest,
      kvstore::GetReply,
      kvstore::RemoveRequest,
      kvstore::RemoveReply;

class KVStoreServer final : public KeyValueStore::Service {
 public:
  Status put(ServerContext*, const PutRequest*, PutReply*) override;
  Status get(ServerContext*, const GetRequest*, ServerWriter<GetReply>*) override;
  Status remove(ServerContext*, const RemoveRequest*, RemoveReply*) override;
 private:
  KVStore store_;
};

#endif // !KVSERVER_H