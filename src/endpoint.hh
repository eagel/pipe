#ifndef PIPE_ENDPOINT_HH_
#define PIPE_ENDPOINT_HH_

#include "stream.hh"

namespace pipe {

class endpoint {
public:
	virtual ~endpoint();

	static endpoint * create(const char *name, bool create_stream);

protected:
	endpoint();
private:
	endpoint(const endpoint &) = delete;
	endpoint & operator=(const endpoint &) = delete;
};

} /* namespace pipe */

#include "endpoint_tcp_client.hh"

#endif /* PIPE_ENDPOINT_HH_ */
