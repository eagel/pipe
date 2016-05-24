#ifndef PIPE_NS_ENDPOINT_TCP_SERVER_HH_
#define PIPE_NS_ENDPOINT_TCP_SERVER_HH_

#include "endpoint.hh"

namespace pipe_ns {

class endpoint_tcp_server: public endpoint {
public:
	virtual ~endpoint_tcp_server();

	static endpoint_tcp_server * create(const char *name, bool positive);
protected:
	endpoint_tcp_server(const char *name, bool positive);
private:
	endpoint_tcp_server(const endpoint_tcp_server &) = delete;
	endpoint_tcp_server & operator=(const endpoint_tcp_server &) = delete;
};

} /* namespace pipe_ns */

#endif /* PIPE_NS_ENDPOINT_TCP_SERVER_HH_ */
