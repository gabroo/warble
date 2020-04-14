#include <glog/logging.h>

#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "kvstore/store.h"

class KVStoreTest : public ::testing::Test {
 protected:
  KVStore store;
  void SetUp() override {
    store.put("key1", "val11");
    store.put("key1", "val12");
    store.put("key2", "val2");
    store.put("key3", "val3");
  }
};

TEST_F(KVStoreTest, ConcurrencyTests) {
  store.put("count", "0");
  auto increment = [this]() {
    int cur = std::stoi((*store.get("count"))[0]);
    store.remove("count");
    store.put("count", std::to_string(cur + 1));
  };
  std::vector<std::thread> q;
  for (int i = 0; i < 100; ++i) {
    q.push_back(std::thread(increment));
  }
  std::for_each(q.begin(), q.end(), [](std::thread& t) { t.join(); });
  std::string result = (*store.get("count"))[0];
  EXPECT_EQ(stoi(result), 100);
}

TEST_F(KVStoreTest, Dump) {
  std::FILE* f = std::fopen("test.txt", "r");
  if (f != nullptr) std::remove("test.txt");
  store.dump("test.txt");
  f = std::fopen("test.txt", "r");
  EXPECT_TRUE(f != nullptr);
}

TEST_F(KVStoreTest, DumpAndRead) {
  store.dump("test.txt");
  KVStore newstore;
  newstore.read("test.txt");
  auto exists = newstore.get("key1");
  std::vector<std::string> vals = *exists;
  EXPECT_EQ((int)vals.size(), 2);
  EXPECT_EQ(vals[0], "val11");
  EXPECT_EQ(vals[1], "val12");
  exists = newstore.get("key2");
  vals = *exists;
  EXPECT_EQ((int)vals.size(), 1);
  EXPECT_EQ(vals[0], "val2");
}

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
  google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
