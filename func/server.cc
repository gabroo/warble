/*
  Sajeev Saluja
  @gabroo
  func/server.cc

  Implements a server that abstracts the execution of functions and their
  storage needs. Functions can use the KVStoreClient object (kvc_) stored
  within the server, which exposes a simple API that eventually makes the
  correct gRPC calls to pass the message to KVStoreServer.

  In this toy example, the server will be pre-compiled with the functions that
  are to be hooked. The HookRequest will thus simply notify the server that a
  particular function is to be used in the current session.
*/

#include "server.h"

Status FuncServer::hook(ServerContext* context, const HookRequest* request, HookReply* reply) {
  return Status::OK;
}

Status FuncServer::unhook(ServerContext* context, const UnhookRequest* request, UnhookReply* reply) {
  return Status::OK;
}

Status FuncServer::event(ServerContext* context, const EventRequest* request, EventReply* reply) {
  return Status::OK;
}

int main () {
  using grpc::Server,
        grpc::ServerBuilder,
        grpc::InsecureServerCredentials,
        grpc::InsecureChannelCredentials,
        grpc::CreateChannel;

  // Initialize func server and connect to port 50000.
  std::string address("0.0.0.0:50000");
  std::string target("0.0.0.0:50001");
  FuncServer server(target);
  ServerBuilder builder;
  builder.AddListeningPort(address, InsecureServerCredentials());
  builder.RegisterService(&server);
  std::unique_ptr<Server> server_ptr(builder.BuildAndStart());
  std::cout << "starting func server on " << address << std::endl;
  server_ptr->Wait();
  return 0;
}
