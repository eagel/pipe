#include "endpoint_tcp_server.hh"

#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream> // FIXME

#include <netdb.h>

#include "exception.hh"

namespace pipe {

class endpoint_tcp_server_i: public endpoint_tcp_server {
	std::string _host;
	unsigned short _port;
	std::vector<int> _sockets;
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
		endpoint_tcp_server(name, positive), _host(""), _port(0), _sockets() {
	int rst;

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
	addrinfo *ais;

	const char *host = _host.c_str();
	std::stringstream ss;
	ss << _port;
	std::string port_s = ss.str();
	const char *port = port_s.c_str();

	addrinfo hint;
	memset(&hint, 0, sizeof(hint));

	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_flags = AI_PASSIVE;

	rst = getaddrinfo(host, port, &hint, &ais);
	if (rst) {
		throw exception(gai_strerror(rst));
	}

	addrinfo *cai = ais;

	while(nullptr != cai){

		std::cout << cai->ai_family << std::endl;

		cai = cai->ai_next;
	}

	freeaddrinfo(ais);
}

endpoint_tcp_server_i::~endpoint_tcp_server_i() {
}

} /* namespace pipe */
