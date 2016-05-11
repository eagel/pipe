#ifndef PIPE_EXCEPTION_HH_
#define PIPE_EXCEPTION_HH_

namespace pipe {

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

} /* namespace pipe */

#endif /* PIPE_EXCEPTION_HH_ */
