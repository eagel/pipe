#ifndef PIPE_ENDPOINT_HH_
#define PIPE_ENDPOINT_HH_

namespace pipe {

class endpoint {
public:
	virtual ~endpoint();

	static endpoint * create(const char *name);
protected:
	endpoint();
private:
	endpoint(const endpoint &) = delete;
	endpoint & operator=(const endpoint &) = delete;
};

} /* namespace pipe */

#endif /* PIPE_ENDPOINT_HH_ */
