#include "functions.h"

bool RegisterUser(Database *db, Any req, Any *rep) {
  RegisterUserRequest request;
  req.UnpackTo(&request);
  std::string username = request.username();
  auto exists = db->get("_users_");
  if (exists) {
    if (std::find((*exists).begin(), (*exists).end(), username) !=
        (*exists).end())
      return false;
    LOG(INFO) << "User " << username << " already exists.";
  }
  db->put("_users_", username);
  LOG(INFO) << "Added user " << username;
  return true;
}

bool Warble(Database *db, Any req, Any *rep) {
  WarbleRequest request;
  req.UnpackTo(&request);
  std::string username = request.username(), text = request.text(),
              parent_id = request.parent_id(), key = "_warbles_" + username;
  std::vector<std::string> hashtags;
  // check if user is registered
  auto exists = db->get("_users_");
  if (exists) {
    if (std::find((*exists).begin(), (*exists).end(), username) ==
        (*exists).end())
      return false;
  } else {
    return false;
  }
  // check if reply is valid
  if (!parent_id.empty()) {
    auto exists = db->get("_warble_" + parent_id);
    if (!exists) {
      LOG(INFO) << "Tried to reply to a warble that does not exist.";
      return false;
    }
  }
  // generate warble id
  std::string warble_id;
  exists = db->get(key);
  if (exists) {
    warble_id = username + std::to_string((*exists).size());
  } else {
    warble_id = username + "0";
  }
  auto secs = std::chrono::seconds(std::time(NULL));
  auto usecs = std::chrono::microseconds(secs).count();
  Timestamp t;
  t.set_seconds(secs.count());
  t.set_useconds(usecs);
  warble::Warble w;
  w.set_username(username);
  w.set_id(warble_id);
  w.set_text(text);
  w.set_parent_id(parent_id);
  *(w.mutable_timestamp()) = t;
  WarbleReply reply;
  *(reply.mutable_warble()) = w;
  rep->PackFrom(reply);
  std::string w_as_string;
  w.SerializeToString(&w_as_string);
  db->put(key, warble_id);
  db->put("_warble_" + warble_id, w_as_string);
  if (!parent_id.empty()) {
    db->put("_reply_" + parent_id, warble_id);
  } else {
    LOG(INFO) << "no parent id found " << parent_id;
  }
  std::istringstream iss(text);
  std::vector<std::string> result{std::istream_iterator<std::string>(iss), {}};
  for (auto r : result) {
    if (r[0] == '#') {
      db->put("_hashtag_" + r, w_as_string);
    }
  }
  return true;
}

bool Follow(Database *db, Any req, Any *rep) {
  FollowRequest request;
  req.UnpackTo(&request);
  std::string username = request.username(), to_follow = request.to_follow();
  // check if both users exist
  std::optional<std::vector<std::string>> users = db->get("_users_");
  if (users) {
    bool found1 = false, found2 = false;
    for (std::string u : *users) {
      if (u.compare(username) == 0)
        found1 = true;
      else if (u.compare(to_follow) == 0)
        found2 = true;
    }
    if (!(found1 && found2)) {
      LOG(INFO) << "Could not find both users for follow request.";
      return false;
    } else {
      db->put("_following_" + username, to_follow);
      db->put("_followers_" + to_follow, username);
      LOG(INFO) << "Added follow relation between " << username << " and "
                << to_follow;
      return true;
    }
  } else {
    return false;
  }
}

bool Read(Database *db, Any req, Any *rep) {
  ReadRequest request;
  ReadReply reply;
  req.UnpackTo(&request);
  std::string id = request.warble_id();
  std::optional<std::vector<std::string>> exists = db->get("_warble_" + id);
  if (exists) {
    warble::Warble *og = reply.add_warbles();
    og->ParseFromString((*exists)[0]);
    std::stack<std::string> s({id});
    while (!s.empty()) {
      std::string cur_id = s.top();
      s.pop();
      std::optional<std::vector<std::string>> replies =
          db->get("_reply_" + cur_id);
      if (replies) {
        for (std::string r : *replies) {
          exists = db->get("_warble_" + r);
          if (exists) {
            warble::Warble *w = reply.add_warbles();
            w->ParseFromString((*exists)[0]);
            s.push(r);
          }
        }
      }
    }
    rep->PackFrom(reply);
    LOG(INFO) << "Found thread starting at " << id;
    return true;
  } else {
    LOG(INFO) << "Could not read thread starting at " << id;
    return false;
  }
}

bool Profile(Database *db, Any req, Any *rep) {
  ProfileRequest request;
  ProfileReply reply;
  req.UnpackTo(&request);
  std::string username = request.username();
  auto exists = db->get("_users_");
  if (exists) {
    if (std::find((*exists).begin(), (*exists).end(), username) ==
        (*exists).end()) {
      LOG(INFO) << "User does not exist.";
      return false;
    }
  } else {
    LOG(INFO) << "User does not exist.";
    return false;
  }
  std::optional<std::vector<std::string>> followers =
      db->get("_followers_" + username);
  if (followers) {
    for (std::string f : *followers) {
      std::string *s = reply.add_followers();
      *s = f;
    }
  }
  std::optional<std::vector<std::string>> following =
      db->get("_following_" + username);
  if (following) {
    for (std::string f : *following) {
      std::string *s = reply.add_following();
      *s = f;
    }
  }
  rep->PackFrom(reply);
  LOG(INFO) << "Got profile for user " << username;
  return true;
}

bool Stream(Database *db, Any req, Any *rep) {
  StreamRequest request;
  StreamReply reply;
  req.UnpackTo(&request);
  std::string hashtag = request.hashtag();
  std::optional<std::vector<std::string>> exists =
      db->get("_hashtag_" + hashtag);
  if (exists) {
    for (auto s : (*exists)) {
      warble::Warble *w = reply.add_warbles();
      w->ParseFromString(s);
    }
    rep->PackFrom(reply);
    LOG(INFO) << "Found warbles with hashtag " << hashtag;
    return true;
  } else {
    LOG(INFO) << "Could not find warbles with hashtag " << hashtag;
    return false;
  }
}