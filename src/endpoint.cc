#include "endpoint.hh"

#include <string>

#include <exception.hh>

namespace pipe_ns {

std::string SCHEMA_TCP_CLIENT = "^";
std::string SCHEMA_TCP_SERVER = "=";
std::string SCHEMA_FILE_DESCRIPTOR = "@";
std::string SCHEMA_FILE_PATH = "%";

endpoint::~endpoint() {
}

endpoint::endpoint() {
}

endpoint * endpoint::create(const char *name, bool positive) {
	std::string n(name);
	if (0 == n.find(SCHEMA_TCP_SERVER)) {
		return endpoint_tcp_server::create(n.substr(1, n.size()).c_str(),
						positive);
	}
	if (0 == n.find(SCHEMA_FILE_DESCRIPTOR)) {
		// TODO
		throw exception("the TCP server endpoint is not supported");
	}
	if (0 == n.find(SCHEMA_FILE_PATH)) {
		// TODO
		throw exception("the TCP server endpoint is not supported");
	}
	if (0 == n.find(SCHEMA_TCP_CLIENT)) {
		return endpoint_tcp_client::create(n.substr(1, n.size()).c_str(),
				positive);
	} else {
		return endpoint_tcp_client::create(name, positive);
	}
}

} /* namespace pipe_ns */
