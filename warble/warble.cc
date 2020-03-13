/*
	Sajeev Saluja
	@gabroo
	warble/warble.cc

	Main program for Warble. Creates and starts a command line interface (CLI).
*/

#include "cli.h"

int main (int argc, char** argv) {
	std::string address("0.0.0.0:50000");
	CLI cli(CreateChannel(address, InsecureChannelCredentials()));
	cli.start();
}