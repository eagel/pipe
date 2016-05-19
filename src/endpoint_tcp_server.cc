#include "endpoint_tcp_server.hh"

#include <string>
#include <cstdlib>
#include <iostream> // FIXME

namespace pipe {

class endpoint_tcp_server_i: public endpoint_tcp_server {
	std::string _host;
	unsigned short _port;
public:
	endpoint_tcp_server_i(const char *name, bool positive);
	virtual ~endpoint_tcp_server_i();
};

endpoint_tcp_server::endpoint_tcp_server(const char *name, bool positive) {
}

endpoint_tcp_server::~endpoint_tcp_server() {
}

endpoint_tcp_server * endpoint_tcp_server::create(const char *name,
		bool positive) {
	return new endpoint_tcp_server_i(name, positive);
}

endpoint_tcp_server_i::endpoint_tcp_server_i(const char *name, bool positive) :
		endpoint_tcp_server(name, positive), _host(""), _port(0) {
	// 1. parse name
	std::string n(name);
	int index = n.find(":");
	if (std::string::npos == index) {
		_host = n;
		_port = 8080;
	} else {
		_host = n.substr(0, index);
		_port = atoi(n.substr(index + 1, n.size()).c_str());
	}

	// 2. create sockets
}

endpoint_tcp_server_i::~endpoint_tcp_server_i() {
}

} /* namespace pipe */
