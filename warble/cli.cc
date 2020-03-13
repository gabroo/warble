/*
  Sajeev Saluja
	@gabroo
	warble/cli.cc

	Implementation of the Warble command line interface.
*/

#include "cli.h"

using grpc::ClientContext,
			grpc::Status,
			google::protobuf::Any,
			func::HookRequest,
			func::HookReply,
			func::EventRequest,
			func::EventReply,
			warble::RegisterUserRequest,
			warble::RegisterUserReply;

void CLI::register_functions() {
	for (size_t i = 0; i < functions_.size(); ++i) {
		std::string str = functions_[i];
		ClientContext context;
		HookRequest req;
		req.set_event_type(i);
		req.set_event_function(str);
		HookReply rep;
		Status s = func_->hook(&context, req, &rep);
		if ((s.ok())) {
			std::cout << "registered function\t" << str << std::endl;
		} else {
			std::cout << "could not register function\t" << str << std::endl;
			std::cout << "error:\t" << s.error_message() << std::endl;
		}
		std::cout << std::endl;
	}
}

void CLI::start() {
	std::cout << "starting warble ...\n" << std::endl;
	std::cout << "registering functions to func ...\n" << std::endl;
	register_functions();
	std::cout << "attempting to register user\tgabroo" << std::endl;
	register_user("gabroo");
	//register_user("another one");
	std::cout << "done with start()" << std::endl;
}

int CLI::find_function(std::string func) {
	for (size_t i = 0; i < functions_.size(); ++i) {
		if (functions_[i].compare(func) == 0) {
			return i;
		}
	}
	return -1;
}

void CLI::register_user(std::string user) {
	ClientContext context;
	RegisterUserRequest ru_req;
	ru_req.set_username(user);
	EventRequest req;
	int event_type = find_function("register_user");
	req.set_event_type(event_type);
	Any rx_payload, tx_payload;
	tx_payload.PackFrom(ru_req);
	*(req.mutable_payload()) = tx_payload;
	EventReply rep;
	std::cout << "(cli.cc) sending address\t" << &req << std::endl;
	Status s = func_->event(&context, req, &rep);
	if ((s.ok())) {
		std::cout << "registered user\t" << user << std::endl;
		// no payload to unpack from rep
		std::cout << "(cli.cc) after event:\t" << &req << std::endl;
	} else {
		std::cout << "could not register user\t" << user << std::endl;
		std::cout << "error:\t" << s.error_message() << std::endl;
	}
	std::cout << std::endl;
}