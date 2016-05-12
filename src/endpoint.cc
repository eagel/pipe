#include "endpoint.hh"

#include <string>

namespace pipe {

std::string SCHEMA_TCP_CLIENT = "^";
std::string SCHEMA_TCP_SERVER = "=";
std::string SCHEMA_FILE_DESCRIPTOR = "@";
std::string SCHEMA_FILE_PATH = "%";

endpoint::~endpoint() {
}

endpoint::endpoint() {
}

endpoint * endpoint::create(const char *name) {
	// TODO
	return nullptr;
}

} /* namespace pipe */
