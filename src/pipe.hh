#ifndef PIPE_NS_PIPE_HH_
#define PIPE_NS_PIPE_HH_

#include "exception.hh"

namespace pipe_ns {

class pipe {
public:
	static pipe * create(int argc, char *argv[]);
public:
	virtual ~pipe();

	virtual int execute() = 0;
protected:
	pipe();
private:
	pipe(const pipe &) = delete;
	pipe & operator=(const pipe &) = delete;
};

} /* namespace pipe_ns */

#endif /* PIPE_NS_PIPE_HH_ */
