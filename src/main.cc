#include <iostream>

#include "pipe.hh"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		pipe::pipe p(argc, argv);
		return p.execute();
	} catch (pipe::exception &e) {
		// TODO
		return -1;
	}
}
