#ifndef PIPE_NS_EXCEPTION_HH_
#define PIPE_NS_EXCEPTION_HH_

namespace pipe_ns {

class exception {
	char * _message;
public:
	exception();
	exception(const char * const &message);
	exception(const exception &e);
	exception(exception &&e);
	virtual ~exception();

	virtual exception & operator =(const exception &e);
	virtual exception & operator =(exception &&e);
	virtual const char * message();
};

} /* namespace pipe_ns */

#endif /* PIPE_NS_EXCEPTION_HH_ */
