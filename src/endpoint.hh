#ifndef PIPE_ENDPOINT_HH_
#define PIPE_ENDPOINT_HH_

#include "stream.hh"

namespace pipe {

class endpoint {
public:
	virtual ~endpoint();

	static endpoint * create(const char *name);

	virtual int read(unsigned char *data, int length) = 0;
	virtual int write(unsigned char *data, int length) = 0;

protected:
	endpoint();
private:
	endpoint(const endpoint &) = delete;
	endpoint & operator=(const endpoint &) = delete;
};

} /* namespace pipe */

#endif /* PIPE_ENDPOINT_HH_ */
