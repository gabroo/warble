#include <vector>
#include "gtest/gtest.h"
#include "kvstore/store.h"

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
  EXPECT_TRUE(store.put("key3", "val31"));
  EXPECT_TRUE(store.put("newkey", "newval"));
}

TEST_F(KVStoreTest, Get) {
  auto exists = store.get("key1");
  auto vals = *exists;
  EXPECT_EQ((int)vals.size(), 2);
  EXPECT_EQ(vals[0], "val11");
  EXPECT_EQ(vals[1], "val12");
  exists = store.get("key2");
  vals = *exists;
  EXPECT_EQ((int)vals.size(), 1);
  EXPECT_EQ(vals[0], "val2");
  exists = store.get("key3");
  vals = *exists;
  EXPECT_EQ((int)vals.size(), 1);
  EXPECT_EQ(vals[0], "val3"); 
  EXPECT_FALSE(exists = store.get("not_a_key"));
}

TEST_F(KVStoreTest, Remove) {
  std::optional<std::vector<std::string>> exists;
  EXPECT_TRUE(store.remove("key1"));
  EXPECT_FALSE(exists = store.get("key1"));
  EXPECT_TRUE(store.remove("key2"));
  EXPECT_FALSE(exists = store.get("key2"));
  EXPECT_TRUE(store.remove("key3"));
  EXPECT_FALSE(exists = store.get("key3"));
  EXPECT_FALSE(store.remove("not_a_key"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
