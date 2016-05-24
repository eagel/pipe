#ifndef PIPE_NS_ENDPOINT_TCP_CLIENT_HH_
#define PIPE_NS_ENDPOINT_TCP_CLIENT_HH_

#include "endpoint.hh"

namespace pipe_ns {

class endpoint_tcp_client: public endpoint {
public:
	virtual ~endpoint_tcp_client();

	static endpoint_tcp_client * create(const char *name, bool positive);
protected:
	endpoint_tcp_client(const char *name, bool positive);
private:
	endpoint_tcp_client(const endpoint_tcp_client &) = delete;
	endpoint_tcp_client & operator=(const endpoint_tcp_client &) = delete;
};

} /* namespace pipe_ns */

#endif /* PIPE_NS_ENDPOINT_TCP_CLIENT_HH_ */
