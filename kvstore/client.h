#include <vector>
#include <optional>
#include <thread>
#include "protos/kvstore.grpc.pb.h"

using kvstore::KeyValueStore,
      grpc::ChannelInterface;

class KVStoreClient {
 public:
  KVStoreClient(std::shared_ptr<ChannelInterface> channel) : stub_(KeyValueStore::NewStub(channel)) {}
  bool put(std::string, std::string);
  std::optional<std::vector<std::string>> get(std::string);
  bool remove(std::string);
 private:
  std::unique_ptr<KeyValueStore::Stub> stub_;
};
