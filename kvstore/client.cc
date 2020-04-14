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
    LOG(ERROR) << s.error_code() << "\t" << s.error_message();
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
    LOG(ERROR) << s.error_code() << "\t" << s.error_message();
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
    LOG(ERROR) << s.error_code() << "\t" << s.error_message();
    return false;
  }
}