#ifndef KVCLIENT_H
#define KVCLIENT_H

#include <vector>
#include <optional>
#include <thread>
#include "protos/kvstore.grpc.pb.h"

using kvstore::KeyValueStore,
      grpc::ChannelInterface;

class KVStoreClient {
 public:
  KVStoreClient(std::shared_ptr<ChannelInterface> channel) : stub_(KeyValueStore::NewStub(channel)) {}
  bool put(std::string, std::string) const;
  std::optional<std::vector<std::string>> get(std::string) const;
  bool remove(std::string) const;
 private:
  std::unique_ptr<KeyValueStore::Stub> stub_;
};

#endif // !KVCLIENT_H