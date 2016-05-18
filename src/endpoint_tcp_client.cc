#include "endpoint_tcp_client.hh"

#include <string>
#include <iostream> // FIXME

namespace pipe {

class endpoint_tcp_client_i: public endpoint_tcp_client {
	std::string _host;
	unsigned short _port;
public:
	endpoint_tcp_client_i(const char *name, bool create_stream);
	virtual ~endpoint_tcp_client_i();
};

endpoint_tcp_client::endpoint_tcp_client(const char *name, bool create_stream) {
}

endpoint_tcp_client::~endpoint_tcp_client() {
}

endpoint_tcp_client * endpoint_tcp_client::create(const char *name,
		bool create_stream) {
	return new endpoint_tcp_client_i(name, create_stream);
}

endpoint_tcp_client_i::endpoint_tcp_client_i(const char *name,
		bool create_stream) :
		endpoint_tcp_client(name, create_stream), _host(""), _port(0) {
	// TODO
}

endpoint_tcp_client_i::~endpoint_tcp_client_i() {
}

} /* namespace pipe */
