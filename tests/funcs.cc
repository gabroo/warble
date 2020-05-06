#include <glog/logging.h>

#include "kvstore/db.h"
#include "kvstore/store.h"
#include "warble/functions.h"
#include "gtest/gtest.h"

class FakeDB : public Database {
public:
  bool put(std::string key, std::string val) { return store_.put(key, val); }
  std::optional<std::vector<std::string>> get(std::string key) {
    return store_.get(key);
  }
  bool remove(std::string key) { return store_.remove(key); }

private:
  KVStore store_;
};

class FuncsTest : public ::testing::Test {
protected:
  FakeDB db;
  void SetUp() override {
    db.put("_users_", "gabroo");
    db.put("_users_", "gabru");
    db.put("_users_", "gabbru");
    db.put("_users_", "gabbroo");
  }
};

TEST_F(FuncsTest, RegisterUser) {
  Any req, rep;
  RegisterUserRequest ru_req;
  ru_req.set_username("test_user");
  req.PackFrom(ru_req);
  EXPECT_TRUE(RegisterUser(&db, req, &rep));
  EXPECT_FALSE(RegisterUser(&db, req, &rep));
}

TEST_F(FuncsTest, WarbleNormal) {
  Any req, rep;
  WarbleRequest w_req;
  w_req.set_username("gabroo");
  w_req.set_text("hello world");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  w_req.set_username("not_a_user_that_exists");
  req.PackFrom(w_req);
  EXPECT_FALSE(Follow(&db, req, &rep));
}

TEST_F(FuncsTest, WarbleValidReply) {
  Any req, rep;
  WarbleRequest w_req;
  w_req.set_username("gabroo");
  w_req.set_text("parent warble");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  WarbleReply w_rep;
  rep.UnpackTo(&w_rep);
  auto id = w_rep.warble().id();
  w_req.set_username("gabroo");
  w_req.set_text("reply warble");
  w_req.set_parent_id(id);
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
}

TEST_F(FuncsTest, WarbleInvalidReply) {
  Any req, rep;
  WarbleRequest w_req;
  w_req.set_username("gabroo");
  w_req.set_text("parent warble");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  WarbleReply w_rep;
  rep.UnpackTo(&w_rep);
  w_req.set_username("gabroo");
  w_req.set_text("reply warble");
  w_req.set_parent_id("not_a_valid_id");
  req.PackFrom(w_req);
  EXPECT_FALSE(Warble(&db, req, &rep));
}

TEST_F(FuncsTest, Follow) {
  Any req, rep;
  FollowRequest f_req;
  f_req.set_username("gabroo");
  f_req.set_to_follow("gabru");
  req.PackFrom(f_req);
  EXPECT_TRUE(Follow(&db, req, &rep));
  f_req.set_to_follow("not_a_user_that_exists");
  req.PackFrom(f_req);
  EXPECT_FALSE(Follow(&db, req, &rep));
}

TEST_F(FuncsTest, Read) {
  Any req, rep;
  WarbleRequest w_req;
  w_req.set_username("gabroo");
  w_req.set_text("hello world");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  w_req.set_username("gabroo");
  w_req.set_text("hello world");
  w_req.set_parent_id("gabroo0");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  ReadRequest r_req;
  r_req.set_warble_id("gabroo0");
  req.PackFrom(r_req);
  EXPECT_TRUE(Read(&db, req, &rep));
  ReadReply r_rep;
  rep.UnpackTo(&r_rep);
  EXPECT_EQ(r_rep.warbles_size(), 2);
}

TEST_F(FuncsTest, Profile) {
  Any req, rep;
  FollowRequest f_req;
  f_req.set_username("gabroo");
  f_req.set_to_follow("gabru");
  req.PackFrom(f_req);
  EXPECT_TRUE(Follow(&db, req, &rep));
  f_req.set_to_follow("gabbroo");
  req.PackFrom(f_req);
  EXPECT_TRUE(Follow(&db, req, &rep));
  f_req.set_to_follow("gabbru");
  req.PackFrom(f_req);
  EXPECT_TRUE(Follow(&db, req, &rep));
  f_req.set_username("gabru");
  f_req.set_to_follow("gabroo");
  req.PackFrom(f_req);
  EXPECT_TRUE(Follow(&db, req, &rep));
  ProfileRequest p_req;
  p_req.set_username("gabroo");
  req.PackFrom(p_req);
  EXPECT_TRUE(Profile(&db, req, &rep));
  ProfileReply p_rep;
  rep.UnpackTo(&p_rep);
  EXPECT_EQ(p_rep.following_size(), 3);
  EXPECT_EQ(p_rep.followers_size(), 1);
}

TEST_F(FuncsTest, Stream) {
  Any req, rep;
  WarbleRequest w_req;
  w_req.set_username("gabroo");
  w_req.set_text("hello world #hello");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  w_req.set_username("gabroo");
  w_req.set_text("hello world #hello");
  w_req.set_parent_id("gabroo0");
  req.PackFrom(w_req);
  EXPECT_TRUE(Warble(&db, req, &rep));
  StreamRequest s_req;
  s_req.set_hashtag("#hello");
  req.PackFrom(s_req);
  EXPECT_TRUE(Stream(&db, req, &rep));
  StreamReply s_rep;
  rep.UnpackTo(&s_rep);
  EXPECT_EQ(s_rep.warbles_size(), 2);
}

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}