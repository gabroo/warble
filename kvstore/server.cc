/*
  Sajeev Saluja
  @gabroo
  kvstore/server.cc

  Implements a key value store service with the following API:
    `put(key, value)` associates `value` with `key` in the store
    `get(key)` returns a stream of values associated with the stream `key`
    `remove(key)` removes the value associated with `key`

  The service is made available via HTTP on port 50001.
*/

#include "server.h"

Status KVStoreServer::put(ServerContext* context, const PutRequest* request,
                          PutReply* response) {
  // Puts the desired key from `request` into the store.
  std::string key = request->key(), value = request->value();
  store_.put(key, value);
  LOG(INFO) << "putting {" << key << ", " << value << "}";
  return Status::OK;
}

Status KVStoreServer::get(ServerContext* context, const GetRequest* request,
                          ServerWriter<GetReply>* stream) {
  // Responds to keys in `stream` with their associated values.
  // If a key is not in the store, theh operation is cancelled.
  std::string key = request->key();
  LOG(INFO) << "getting {" << key << "}";
  if (auto values =
          store_.get(key)) {  // empty vector indicates key not in store
    for (std::string v : *values) {
      GetReply reply;
      reply.set_value(v);
      stream->Write(reply, WriteOptions());
    }
  } else {
    return Status::CANCELLED;
  }
  return Status::OK;
}

Status KVStoreServer::remove(ServerContext* context,
                             const RemoveRequest* request,
                             RemoveReply* response) {
  // Removes the key value pair associated with the key in `request`.
  // If the key is invalid, it does nothing.
  std::string key = request->key();
  LOG(INFO) << "removing {" << key << "}";
  store_.remove(key);
  return Status::OK;
}

void KVStoreServer::dump(const std::string &file) {
  store_.dump(file);
}

void KVStoreServer::read(const std::string &file) {
  store_.read(file);
}

DEFINE_string(file, "", "File from/to which to read/write the contents of the store.");

// must be global to support access from signalHandler
KVStoreServer server;

void signalHandler(int i) {
  std::cout << "caught signal\t" << i << std::endl;
  server.dump(FLAGS_file);
  exit(i);
}

int main(int argc, char** argv) {
  using grpc::Server, grpc::ServerBuilder, grpc::InsecureServerCredentials;

  google::InitGoogleLogging(argv[0]);
  gflags::SetUsageMessage("Please run  with -h flag to see usage");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  
  // link termination/interrupt signals to the handler function
  if (FLAGS_file != "") {
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);
    server.read(FLAGS_file);
  }

  // Initializes a key value store service and connects it to port 50001.
  std::string address("0.0.0.0:50001");
  ServerBuilder builder;
  builder.AddListeningPort(address, InsecureServerCredentials());
  builder.RegisterService(&server);
  std::unique_ptr<Server> server_ptr(builder.BuildAndStart());
  std::cout << "starting key value store on " << address << std::endl;
  server_ptr->Wait();
  return 0;
}
