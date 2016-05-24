#ifndef PIPE_NS_ENDPOINT_HH_
#define PIPE_NS_ENDPOINT_HH_

#include "stream.hh"

namespace pipe_ns {

class endpoint {
public:
	virtual ~endpoint();

	static endpoint * create(const char *name, bool positive);

protected:
	endpoint();
private:
	endpoint(const endpoint &) = delete;
	endpoint & operator=(const endpoint &) = delete;
};

} /* namespace pipe_ns */

#include "endpoint_tcp_client.hh"
#include "endpoint_tcp_server.hh"

#endif /* PIPE_NS_ENDPOINT_HH_ */
