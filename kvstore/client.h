#ifndef KVCLIENT_H
#define KVCLIENT_H

#include <optional>
#include <thread>
#include <vector>

#include "db.h"
#include "protos/kvstore.grpc.pb.h"

using kvstore::KeyValueStore, grpc::ChannelInterface;

// A Database client that is specific to the gRPC-loaded KVStoreServer (see kvstore/server.h)
class KVStoreClient : public Database {
 public:
  KVStoreClient(std::shared_ptr<ChannelInterface> channel)
      : stub_(KeyValueStore::NewStub(channel)) {}
  bool put(std::string, std::string);
  std::optional<std::vector<std::string>> get(std::string);
  bool remove(std::string);

 private:
  // Pointer to the gRPC client stub
  std::unique_ptr<KeyValueStore::Stub> stub_;
};

#endif  // !KVCLIENT_H