#ifndef PIPE_PIPE_HH_
#define PIPE_PIPE_HH_

#include "exception.hh"

namespace pipe {

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

} /* namespace pipe */

#endif /* PIPE_PIPE_HH_ */
