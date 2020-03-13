/*
	Sajeev Saluja
	@gabroo
	warble/warble.cc

	Main program for Warble. Creates and starts a command line interface (CLI).
*/

#include "cli.h"
#include <glog/logging.h>
#include "gflags/gflags.h"

DEFINE_string(registeruser, "", "Registers the given username");
DEFINE_string(user, "", "Logs in as the given username");
DEFINE_string(warble, "", "Creates a new warble with the given text");
DEFINE_string(reply, "", "Indicates that the new warble is a reply to the given id");
DEFINE_string(follow, "", "Starts following the given username");
DEFINE_string(read, "", "Reads the warble thread starting at the given id");
DEFINE_bool(profile, false, "Gets the user's profile of following and followers");

int main (int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);
	gflags::SetUsageMessage("Please run  <warble -h>  to see usage");
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	std::string address("0.0.0.0:50000");
	CLI cli(CreateChannel(address, InsecureChannelCredentials()));
	if (FLAGS_registeruser == "" && FLAGS_user == "") {
		std::cout << "Must specify either --registeruser (to sign up) or --user (to log in).\n";
		return 1;
	} else {
		if (FLAGS_registeruser != "") {
			cli.RegisterUser(FLAGS_registeruser);
		} else {
			if (FLAGS_user == "") {
				std::cout << "Must login with the --user flag.\n";
				return 2;
			} else {
				if (FLAGS_warble != "" && FLAGS_read == "" && !FLAGS_profile && FLAGS_follow == "") {
					cli.Warble(FLAGS_user, FLAGS_warble, FLAGS_reply);
				} else if (FLAGS_warble == "" && FLAGS_read != "" && !FLAGS_profile && FLAGS_follow == "") {
					cli.Read(FLAGS_read);
				} else if (FLAGS_warble == "" && FLAGS_read == "" && FLAGS_profile && FLAGS_follow == "") {
					cli.Profile(FLAGS_user);
				} else if (FLAGS_warble == "" && FLAGS_read == "" && !FLAGS_profile && FLAGS_follow != "") {
					cli.Follow(FLAGS_user, FLAGS_follow);
				} else {
					std::cout << "Must specify at least one of {--warble, --read, --profile, --follow}.\n";
					return 3;
				}
			}
		}
	}
	return 0;
}