#include "client.h"

using grpc::Status, grpc::ClientContext, grpc::ClientReader, kvstore::PutReply,
    kvstore::PutRequest, kvstore::GetRequest, kvstore::GetReply,
    kvstore::RemoveRequest, kvstore::RemoveReply;

bool KVStoreClient::put(std::string key, std::string value) {
  ClientContext context;
  PutRequest request;
  request.set_key(key);
  request.set_value(value);
  PutReply reply;
  Status s = stub_->put(&context, request, &reply);
  if (s.ok()) {
    return true;
  } else {
    std::cout << s.error_code() << "\t" << s.error_message() << std::endl;
    return false;
  }
}

std::optional<std::vector<std::string>> KVStoreClient::get(std::string key) {
  ClientContext context;
  GetRequest request;
  request.set_key(key);
  std::unique_ptr<ClientReader<GetReply>> reader(stub_->get(&context, request));
  std::vector<std::string> values;
  GetReply reply;
  while (reader->Read(&reply)) {
    std::string value = reply.value();
    values.push_back(value);
  }
  Status s = reader->Finish();
  if (s.ok()) {
    return values;
  } else {
    std::cout << s.error_code() << "\t" << s.error_message() << std::endl;
    return std::nullopt;
  }
}

bool KVStoreClient::remove(std::string key) {
  ClientContext context;
  RemoveRequest request;
  request.set_key(key);
  RemoveReply reply;
  Status s = stub_->remove(&context, request, &reply);
  if (s.ok()) {
    return true;
  } else {
    std::cout << s.error_code() << "\t" << s.error_message() << std::endl;
    return false;
  }
}