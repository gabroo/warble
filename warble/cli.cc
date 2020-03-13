/*
  Sajeev Saluja
        @gabroo
        warble/cli.cc

        Implementation of the Warble command line interface.
*/

#include "cli.h"

using grpc::ClientContext, grpc::Status, google::protobuf::Any,
    func::HookRequest, func::HookReply, func::EventRequest, func::EventReply,
    warble::RegisterUserRequest, warble::RegisterUserReply,
    warble::WarbleRequest, warble::WarbleReply, warble::FollowRequest,
    warble::FollowReply, warble::ReadRequest, warble::ReadReply,
    warble::ProfileRequest, warble::ProfileReply;

void CLI::RegisterFunctions() {
  for (size_t i = 0; i < functions_.size(); ++i) {
    std::string str = functions_[i];
    ClientContext context;
    HookRequest req;
    req.set_event_type(i);
    req.set_event_function(str);
    HookReply rep;
    Status s = func_->hook(&context, req, &rep);
    if ((s.ok())) {
      LOG(INFO) << "registered function" << str;
    } else {
      LOG(INFO) << "could not register function " << str;
      LOG(INFO) << "error: " << s.error_message();
    }
  }
}

int CLI::find_event_type_(std::string func) {
  for (size_t i = 0; i < functions_.size(); ++i) {
    if (functions_[i].compare(func) == 0) {
      LOG(INFO) << "Found event type " << i << " for function " << func;
      return i;
    }
  }
  return -1;
}

void CLI::RegisterUser(std::string user) {
  ClientContext context;
  RegisterUserRequest ru_req;
  ru_req.set_username(user);
  EventRequest req;
  int event_type = find_event_type_("register_user");
  req.set_event_type(event_type);
  Any rx_payload, tx_payload;
  tx_payload.PackFrom(ru_req);
  *(req.mutable_payload()) = tx_payload;
  EventReply rep;
  Status s = func_->event(&context, req, &rep);
  if ((s.ok())) {
    LOG(INFO) << "Registered user " << user;
    std::cout << "Success: " << user << " is registered.";
  } else {
    LOG(INFO) << "error: " << s.error_message();
    std::cout << "Could not register user " << user;
  }
  std::cout << std::endl;
}

void CLI::Warble(std::string user, std::string text, std::string parent) {
  ClientContext context;
  WarbleRequest w_req;
  w_req.set_username(user);
  w_req.set_text(text);
  w_req.set_parent_id(parent);
  EventRequest req;
  int event_type = find_event_type_("warble");
  req.set_event_type(event_type);
  Any rx_payload, tx_payload;
  tx_payload.PackFrom(w_req);
  *(req.mutable_payload()) = tx_payload;
  EventReply rep;
  Status s = func_->event(&context, req, &rep);
  if (s.ok()) {
    rx_payload = rep.payload();
    WarbleReply w_rep;
    rx_payload.UnpackTo(&w_rep);
    warble::Warble w = w_rep.warble();
    std::cout << "Your warble has been posted. The ID of this warble is:\n"
              << w.id();
    LOG(INFO) << "Warble posted from user " << user;
  } else {
    std::cout << "Could not post the warble. Please make sure you are signed "
                 "up and logged in.";
    LOG(INFO) << "Warble could not be posted.";
  }
  std::cout << std::endl;
}

void CLI::Follow(std::string user, std::string to_follow) {
  ClientContext context;
  FollowRequest f_req;
  f_req.set_username(user);
  f_req.set_to_follow(to_follow);
  EventRequest req;
  int event_type = find_event_type_("follow");
  req.set_event_type(event_type);
  Any rx_payload, tx_payload;
  tx_payload.PackFrom(f_req);
  *(req.mutable_payload()) = tx_payload;
  EventReply rep;
  Status s = func_->event(&context, req, &rep);
  if ((s.ok())) {
    std::cout << "Successfully followed " << to_follow;
    LOG(INFO) << "Follow relation added from " << user << " to " << to_follow;
  } else {
    LOG(INFO) << "Follow error:" << s.error_message();
    std::cout << "Could not perform the follow.";
  }
  std::cout << std::endl;
}

void CLI::Read(std::string id) {
  ClientContext context;
  ReadRequest r_req;
  r_req.set_warble_id(id);
  EventRequest req;
  int event_type = find_event_type_("read");
  req.set_event_type(event_type);
  Any rx_payload, tx_payload;
  tx_payload.PackFrom(r_req);
  *(req.mutable_payload()) = tx_payload;
  EventReply rep;
  Status s = func_->event(&context, req, &rep);
  if ((s.ok())) {
    std::cout << "Thread: (starting at " << id << ")\n\n";
    rx_payload = rep.payload();
    ReadReply r_rep;
    rx_payload.UnpackTo(&r_rep);
    size_t num_warbles = r_rep.warbles_size();
    for (size_t i = 0; i < num_warbles; ++i) {
      warble::Warble w = r_rep.warbles(i);
      std::string user = w.username(), text = w.text(), id = w.id(),
                  parent = w.parent_id();
      time_t t = w.timestamp().seconds();
      std::cout << "(id " << id << ")\n";
      std::cout << asctime(gmtime(&t));
      std::cout << "[" << user << "]:\t" << text << "\n";
      if (parent.size()) std::cout << "(reply to: " + parent + ")\n";
      std::cout << std::endl;
    }
  } else {
    std::cout << "Could not find thread starting at " << id << std::endl;
    LOG(INFO) << "Read error: " << s.error_message();
  }
}

void CLI::Profile(std::string username) {
  ClientContext context;
  ProfileRequest p_req;
  p_req.set_username(username);
  EventRequest req;
  int event_type = find_event_type_("profile");
  req.set_event_type(event_type);
  Any rx_payload, tx_payload;
  tx_payload.PackFrom(p_req);
  *(req.mutable_payload()) = tx_payload;
  EventReply rep;
  Status s = func_->event(&context, req, &rep);
  if ((s.ok())) {
    rx_payload = rep.payload();
    ProfileReply p_rep;
    rx_payload.UnpackTo(&p_rep);
    std::cout << username << "'s profile:\n";
    size_t n_followers = p_rep.followers_size(),
           n_following = p_rep.following_size();
    if (n_followers) {
      std::cout << "followers:\t";
      for (size_t i = 0; i < n_followers; ++i) {
        std::cout << p_rep.followers(i);
        if (i != n_followers - 1)
          std::cout << ", ";
        else
          std::cout << ".";
      }
      std::cout << std::endl;
    } else {
      std::cout << "no followers\n";
    }
    std::cout << std::endl;
    if (n_following) {
      std::cout << "following:\t";
      for (size_t i = 0; i < n_following; ++i) {
        std::cout << p_rep.following(i);
        if (i != n_following - 1)
          std::cout << ", ";
        else
          std::cout << ".";
      }
      std::cout << std::endl;
    } else {
      std::cout << "not following anyone\n";
    }
    std::cout << std::endl;
  } else {
    std::cout << "Could not find profile for user " << username << std::endl;
    LOG(INFO) << "error: " << s.error_message();
  }
}