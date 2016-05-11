#ifndef PIPE_PIPE_HH_
#define PIPE_PIPE_HH_

#include "exception.hh"

namespace pipe {

class pipe {
public:
	pipe(int argc, char *argv[]);

	int execute();
};

} /* namespace pipe */

#endif /* PIPE_PIPE_HH_ */
