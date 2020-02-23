/*
  Sajeev Saluja
  @gabroo
  kvstore_service.cc

  Implements a key value store service with the following API:
    `put(key, value)` associates `value` with `key` in the store
    `get(key)` returns a stream of values associated with the stream `key` 
    `remove(key)` removes the value associated with `key`

  The service is made available via HTTP on port 50001.
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

class KeyValueService final : public KeyValueStore::Service {
 public:
  Status put(ServerContext* context, const PutRequest* request, PutReply* response) {
    // Puts the desired key from `request` into the store.
    std::string key = request->key(), value = request->value();
    store_.put(key, value);
    return Status::OK; 
  }
  
  Status get(ServerContext* context, ServerReaderWriter<GetReply, GetRequest>* stream) {
    // Responds to keys in `stream` with their associated values.
    // If a key is not in the store, theh operation is cancelled.
    GetRequest request;
    while (stream->Read(&request)) {
      std::string key = request.key();
      std::vector<std::string> values = store_.get(key);
      if (values.size() == 0) { // empty vector indicates key not in store
        return Status::CANCELLED;
      } else {
        GetReply reply;
        for (std::string v : values) {
          reply.set_value(v);
          stream->Write(reply, WriteOptions());
        }
      }
    } 
    return Status::OK;
  }

  Status remove(ServerContext* context, const RemoveRequest* request, RemoveReply* response) {
    // Removes the key value pair associated with the key in `request`.
    // If the key is invalid, it does nothing.
    std::string key = request->key();
    store_.remove(key);
    return Status::OK;
  }
 private:
  KVStore store_;
};

int main () {
  using grpc::Server;
  using grpc::ServerBuilder;
  using grpc::InsecureServerCredentials;
  // Initializes a key value store service and connects it to port 50001.
  std::string address("0.0.0.0:50001");
  KeyValueService service;
  ServerBuilder builder;
  builder.AddListeningPort(address, InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "starting key value store on " << address << std::endl;
  server->Wait();
  return 0;
}
