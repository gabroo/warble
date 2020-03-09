/*
  Sajeev Saluja
	@gabroo
	warble/cli.h

	Forward declarations for the Warble command line interface.
*/

#include <grpc++/grpc++.h>
#include "protos/warble.pb.h"
#include "protos/func.grpc.pb.h"

using grpc::Channel,
			grpc::CreateChannel,
			grpc::InsecureChannelCredentials,
			func::FuncService;

class CLI {
 public:
	CLI(std::shared_ptr<Channel> channel) : stub_(FuncService::NewStub(channel)) {};
	void start(); // starts the CLI
 private:
  std::unique_ptr<FuncService::Stub> stub_; // interface to Func
};

int main (int argc, char** argv) {
	std::string address("0.0.0.0:50000");
	CLI cli(CreateChannel(address, InsecureChannelCredentials()));
	cli.start();
}
