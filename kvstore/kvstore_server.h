/*
  Sajeev Saluja
  @gabroo
  kvstore_server.h

  Forward declarations for kvstore_server.cc
*/

#include <iostream>
#include <unordered_map>
#include <grpcpp/grpcpp.h>
#include "protos/kvstore.grpc.pb.h"
#include "kvstore.h"

using grpc::Status;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::WriteOptions;
using kvstore::KeyValueStore;
using kvstore::PutRequest;
using kvstore::PutReply;
using kvstore::GetRequest;
using kvstore::GetReply;
using kvstore::RemoveRequest;
using kvstore::RemoveReply;

class KeyValueServer final : public KeyValueStore::Service {
 public:
  Status put(ServerContext*, const PutRequest*, PutReply*);
  Status get(ServerContext*, ServerReaderWriter<GetReply, GetRequest>*);
  Status remove(ServerContext*, const RemoveRequest*, RemoveReply*);
 private:
  KVStore store_;
};
