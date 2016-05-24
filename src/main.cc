#include <iostream>

#include "pipe.hh"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		pipe_ns::pipe *p = pipe_ns::pipe::create(argc, argv);
		return p->execute();
	} catch (pipe_ns::exception &e) {
		cout << e.message() << endl;
		return -1;
	}
}
