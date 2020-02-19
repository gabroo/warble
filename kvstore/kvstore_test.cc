/*
  Sajeev Saluja
  @gabroo
  kvstore_test.cc

  Tests all public functions defined in the `KeyValueService` class.
*/

#include <gtest/gtest.h>
#include <grpc++/grpc++.h>
#include "kvstore_mock.grpc.pb.h"
#include <iostream>

using namespace kvstore;
using namespace grpc;

class KeyValueTest {
 public:
  // Construct from `StubInterface*`
  explicit KeyValueTest(KeyValueStore::StubInterface* stub) : stub_(stub) {}

  void TestPut() {
    // `Status put(ServerContext*, const PutRequest*, PutReply*)`
    ClientContext context;
    PutRequest request;
    PutResponse response;
    for (char i = '1'; i <= '10'; ++i) {
      request.set_key("key"+i);
      request.set_value("value"+i);
      Status s = stub_->put(&context, &request, &response);
      EXPECT_TRUE(s.ok());
    }
  }

  void TestGet() {
    // `Status get(ServerContext*, ServerReaderWriter<GetReply, GetRequest>*)`
    ClientContext context;
    PutRequest prequest;
    PutResponse presponse;
    GetRequest grequest;
    GetResponse gresponse;
    for (char i = '1'; i <= '10'; ++i) {
      std::string key = "key"+i, value = "value"+i;
      prequest.set_key(key);
      prequest.set_value(value);
      // (???) do we assume that `put` works correctly?
      Status s = stub_->put(&context, &prequest, &presponse);
      grequest.set_key(key);
      s = stub_->get(&context, &grequest, &gresponse);
      EXPECT_TRUE(s.ok());
      EXPECT_EQ(value, greponse.value());
    }
  }

  void TestRemove() {
    // `Status remove(ServerContext*, const RemoveRequest*, RemoveReply*)`
  }
 private:
  KeyValueStore::StubInterface* stub_;
}

int main(int argc, char** argv) {
  testing::TestEnvironment env(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
