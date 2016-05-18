#include "endpoint_tcp_server.hh"

#include <string>
#include <iostream> // FIXME

namespace pipe {

class endpoint_tcp_server_i: public endpoint_tcp_server {
	std::string _host;
	unsigned short _port;
public:
	endpoint_tcp_server_i(const char *name, bool create_stream);
	virtual ~endpoint_tcp_server_i();
};

endpoint_tcp_server::endpoint_tcp_server(const char *name, bool create_stream) {
}

endpoint_tcp_server::~endpoint_tcp_server() {
}

endpoint_tcp_server * endpoint_tcp_server::create(const char *name,
		bool create_stream) {
	return new endpoint_tcp_server_i(name, create_stream);
}

endpoint_tcp_server_i::endpoint_tcp_server_i(const char *name,
		bool create_stream) :
		endpoint_tcp_server(name, create_stream), _host(""), _port(0) {
	// TODO
}

endpoint_tcp_server_i::~endpoint_tcp_server_i() {
}

} /* namespace pipe */
