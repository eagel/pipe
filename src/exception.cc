#include "exception.hh"

#include <cstring>

using namespace std;

namespace pipe_ns {
exception::exception() :
		_message(nullptr) {
}
exception::exception(const char * const &message) :
		_message(strcpy(new char[strlen(message)], message)) {
}
exception::exception(const exception &e) :
		_message(strcpy(new char[strlen(e._message)], e._message)) {
}
exception::exception(exception &&e) :
		_message(e._message) {
	e._message = nullptr;
}
exception::~exception() {
	if (nullptr != _message) {
		delete _message;
	}
}

exception & exception::operator =(const exception &e) {
	if (nullptr != _message) {
		delete _message;
	}
	_message = strcpy(new char[strlen(e._message)], e._message);
	return *this;
}
exception & exception::operator =(exception &&e) {
	if (nullptr != _message) {
		delete _message;
	}
	_message = e._message;
	e._message = nullptr;
	return *this;
}

const char * exception::message() {
	if (nullptr == _message) {
		return "";
	} else {
		return _message;
	}
}
} /* namespace pipe_ns */
