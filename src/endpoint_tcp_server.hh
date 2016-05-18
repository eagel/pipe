#ifndef PIPE_ENDPOINT_TCP_SERVER_HH_
#define PIPE_ENDPOINT_TCP_SERVER_HH_

#include "endpoint.hh"

namespace pipe {

class endpoint_tcp_server: public endpoint {
public:
	virtual ~endpoint_tcp_server();

	static endpoint_tcp_server * create(const char *name, bool create_stream);
protected:
	endpoint_tcp_server(const char *name, bool create_stream);
private:
	endpoint_tcp_server(const endpoint_tcp_server &) = delete;
	endpoint_tcp_server & operator=(const endpoint_tcp_server &) = delete;
};

} /* namespace pipe */

#endif /* PIPE_ENDPOINT_TCP_SERVER_HH_ */
