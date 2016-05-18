#include "endpoint.hh"

#include <string>

#include <exception.hh>

namespace pipe {

std::string SCHEMA_TCP_CLIENT = "^";
std::string SCHEMA_TCP_SERVER = "=";
std::string SCHEMA_FILE_DESCRIPTOR = "@";
std::string SCHEMA_FILE_PATH = "%";

endpoint::~endpoint() {
}

endpoint::endpoint() {
}

endpoint * endpoint::create(const char *name, bool create_stream) {
	std::string n(name);
	if (0 == n.find(SCHEMA_TCP_SERVER)) {
		return endpoint_tcp_server::create(n.substr(1, n.size()).c_str(),
						create_stream);
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
				create_stream);
	} else {
		return endpoint_tcp_client::create(name, create_stream);
	}
}

} /* namespace pipe */
