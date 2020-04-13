/*
  Sajeev Saluja
  @gabroo
  kvstore/server.h

  Forward declarations for kvstore/server.cc
*/

#ifndef KVSERVER_H
#define KVSERVER_H

#include <glog/logging.h>
#include <grpc++/grpc++.h>

#include <iostream>
#include <unordered_map>

#include "protos/kvstore.grpc.pb.h"
#include "store.h"
#include "gflags/gflags.h"

using grpc::Status, grpc::ServerContext, grpc::ServerWriter, grpc::WriteOptions,
    kvstore::KeyValueStore, kvstore::PutRequest, kvstore::PutReply,
    kvstore::GetRequest, kvstore::GetReply, kvstore::RemoveRequest,
    kvstore::RemoveReply;

// Creates and starts a server that exposes a key value store API
class KVStoreServer final : public KeyValueStore::Service {
 public:
  // Allows for multiple values associated with each key.
  Status put(ServerContext*, const PutRequest*, PutReply*) override;
  // Returns all values associated with a key.
  Status get(ServerContext*, const GetRequest*,
             ServerWriter<GetReply>*) override;
  // Removes all values associated with a key.
  Status remove(ServerContext*, const RemoveRequest*, RemoveReply*) override;
  // Tells the KVStore server to dump its contents to a file
  void dump(const std::string&);
  // Tells the KVStore server to read its contents from a file
  void read(const std::string&);
 private:
  KVStore store_;
};

#endif  // !KVSERVER_H