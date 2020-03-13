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
  int event_type = request->event_type();
  std::string event_function = request->event_function();
  if (events_.find(event_type) == events_.end()) {
    events_.insert({event_type, event_function});
    LOG(INFO) << "hooked function " << event_function << " to type " << event_type;
    return Status::OK;
  } else {
    LOG(INFO) << "function already hooked " << event_function;
    return Status::CANCELLED;
  }
}

Status FuncServer::unhook(ServerContext* context, const UnhookRequest* request, UnhookReply* reply) {
  int event_type = request->event_type();
  if (events_.find(event_type) == events_.end()) {
    LOG(INFO) << "event type " << event_type << " not already in use.";
    return Status::CANCELLED;
  } else {
    LOG(INFO) << "erased " << event_type;
    events_.erase(event_type);
    return Status::OK;
  }
  return Status::OK;
}

Status FuncServer::event(ServerContext* context, const EventRequest* request, EventReply* reply) {
  int event_type = request->event_type();
  if (events_.find(event_type) == events_.end()) {
    return Status::CANCELLED;
  } else {
    std::string event_function = events_[event_type];
    Any tx_payload = request->payload();
    fn function = funcs[event_function]; // fn defined in functions.h (warble function)
    Any rx_payload;
    bool ok = function(&db_, tx_payload, &rx_payload);
    *(reply->mutable_payload()) = rx_payload;
    if (ok) {
      LOG(INFO) << "received event\t" << event_function;
      return Status::OK;
    } else {
      LOG(INFO) << "could not execute event\t" << event_function;
      return Status::CANCELLED;
    }
  }
}

int main (int argc, char** argv) {
  using grpc::Server,
        grpc::ServerBuilder,
        grpc::InsecureServerCredentials,
        grpc::InsecureChannelCredentials,
        grpc::CreateChannel;

  google::InitGoogleLogging(argv[0]);
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
