#include "endpoint_tcp_server.hh"

#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream> // FIXME

#include <netdb.h>
#include <unistd.h>

#include "exception.hh"

namespace pipe_ns {

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

	// 2.1 parse host and port
	const char *host = _host.c_str();
	std::stringstream ss;
	ss << _port;
	std::string port_s = ss.str();
	const char *port = port_s.c_str();

	// 2.2 retrieve socket address informations.
	addrinfo hint;
	memset(&hint, 0, sizeof(hint));

	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_flags = AI_PASSIVE;

	addrinfo *ais;

	rst = getaddrinfo(host, port, &hint, &ais);
	if (rst) {
		throw exception(gai_strerror(rst));
	}

	// 2.3 create sockets
	addrinfo *cai = ais;

	while (nullptr != cai) {

		// 2.3.1 create socket
		int s = socket(cai->ai_family, cai->ai_socktype, cai->ai_protocol);

		if (-1 == s) {
			throw exception(strerror(errno));
		}

		// 2.3.2 add socket to opened sockets
		_sockets.push_back(s);

		// 2.3.3 bind socket to a address
		rst = bind(s, cai->ai_addr, cai->ai_addrlen);

		if (-1 == rst) {
			std::string msg = std::string() + "bind socket to " + name + ": "
					+ strerror(errno);
			throw exception(msg.c_str());
		}

		// 2.3.4 set the socket to listen
		rst = listen(s, 100);
		if (-1 == rst) {
			std::string msg = std::string() + "listen socket to " + name + ": "
								+ strerror(errno);
			throw exception(msg.c_str());
		}

		// TODO may need set to asynchronized

		cai = cai->ai_next;
	}

	// 2.4 release socket address informations.
	freeaddrinfo(ais);
}

endpoint_tcp_server_i::~endpoint_tcp_server_i() {
	for (std::vector<int>::iterator i = _sockets.begin(); i != _sockets.end();
			++i) {
		close(*i);
	}
}

} /* namespace pipe */
