#include <iostream>

#include "pipe.hh"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		pipe::pipe *p = pipe::pipe::create(argc, argv);
		return p->execute();
	} catch (pipe::exception &e) {
		cout << e.message() << endl;
		return -1;
	}
}
