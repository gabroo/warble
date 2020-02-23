#include <vector>
#include "gtest/gtest.h"
#include "kvstore/kvstore.h"

using std::vector;
using std::string;

class KVStoreTest : public ::testing::Test {
 protected:
  KVStore store;
  void SetUp() override {
    store = KVStore();
    store.put("key1", "val11");
    store.put("key1", "val12");
    store.put("key2", "val2");
    store.put("key3", "val3");
  }
};

TEST_F(KVStoreTest, Put) {
  EXPECT_EQ(store.put("key3", "val31"), 0);
  EXPECT_EQ(store.put("newkey", "newval"), 0);
}

TEST_F(KVStoreTest, Get) {
  vector<string> vals;
  vals = store.get("key1");
  EXPECT_EQ((int)vals.size(), 2);
  EXPECT_EQ(vals[0], "val11");
  EXPECT_EQ(vals[1], "val12");
  vals = store.get("key2");
  EXPECT_EQ((int)vals.size(), 1);
  EXPECT_EQ(vals[0], "val2");
  vals = store.get("key3");
  EXPECT_EQ((int)vals.size(), 1);
  EXPECT_EQ(vals[0], "val3"); 
}

TEST_F(KVStoreTest, Remove) {
  vector<string> vals;
  EXPECT_EQ(store.remove("key1"), 0);
  vals = store.get("key1");
  EXPECT_EQ((int)vals.size(), 0);
  EXPECT_EQ(store.remove("key2"), 0);
  vals = store.get("key2");
  EXPECT_EQ((int)vals.size(), 0);
  EXPECT_EQ(store.remove("key3"), 0);
  vals = store.get("key3");
  EXPECT_EQ((int)vals.size(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
