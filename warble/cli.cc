#include "cli.h"

void CLI::start() {

}

int main (int argc, char** argv) {
	std::string address("0.0.0.0:50000");
	CLI cli(CreateChannel(address, InsecureChannelCredentials()));
	cli.start();
}