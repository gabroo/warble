/*
  Sajeev Saluja
	@gabroo
	warble/cli.h

	Forward declarations for the Warble command line interface.
	See cli.cc for implementation details.

	The following options are supported:
		--registeruser <username>			Registers the given username
		--user <username>							Logs in as the given username
		--warble <warble text>				Creates a new warble with the given text
		--reply <reply warble id>			Indicates that the new warble is a reply to the given id
		--follow <username>						Starts following the given username
		--read <warble id>						Reads the warble thread starting at the given id
		--profile											Gets the user’s profile of following and followers
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <grpc++/grpc++.h>
#include "protos/warble.pb.h"
#include "protos/func.grpc.pb.h"

using grpc::ChannelInterface,
			grpc::CreateChannel,
			grpc::InsecureChannelCredentials,
			func::FuncService;

class CLI {
 public:
	CLI(std::shared_ptr<ChannelInterface> channel) : func_(FuncService::NewStub(channel)), functions_({
		"register_user",
		"warble",
		"follow",
		"read"
	}) {};
	void start();
	void register_functions();
	void register_user(std::string);
 private:
 	int find_function(std::string);
  std::unique_ptr<FuncService::Stub> func_; // interface to Func
	std::vector<std::string> functions_;
};
