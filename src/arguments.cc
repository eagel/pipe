#include "arguments.hh"

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "exception.hh"

using namespace std;

namespace {
class arguments_i {
public:
	string _name;
	vector<string> _names;
	map<string, pipe_ns::arguments::type_t> _types;
	map<string, string> _aliases;
	map<string, string> _values;
	map<string, string> _defaults;
	vector<string> _errorsNames;
	vector<string> _errorsMessages;

	static arguments_i * cast(void *implementation) {
		return static_cast<arguments_i *>(implementation);
	}
};

}

namespace pipe_ns {

const char * const arguments::TRUE = "true";
const char * const arguments::FALSE = "false";
const char * const arguments::NONE = "";

arguments::arguments() :
		_implementation(new arguments_i()) {
}

arguments::arguments(const arguments & args) :
		_implementation(
				new arguments_i(*arguments_i::cast(args._implementation))) {
}

arguments::arguments(arguments && args) :
		_implementation(args._implementation) {
	args._implementation = nullptr;
}

arguments::~arguments() {
	if (nullptr != _implementation) {
		delete arguments_i::cast(_implementation);
	}
}

arguments & arguments::operator=(const arguments & args) {
	(*arguments_i::cast(_implementation)) = *arguments_i::cast(
			args._implementation);
	return *this;
}
arguments & arguments::operator=(arguments && args) {
	delete arguments_i::cast(_implementation);
	_implementation = args._implementation;
	args._implementation = nullptr;
	return *this;
}

arguments & arguments::configure(const char * name, const char * alias,
		type_t type) {
	switch (type) {
	case TYPE_VALUE:
		return configure(name, alias, type, NONE);
	case TYPE_FLAG:
		return configure(name, alias, type, FALSE);
	case TYPE_CONFIG:
		return configure(name, alias, type, TRUE);
	default:
		return configure(name, alias, type, NONE);
	}
}

arguments & arguments::configure(const char * name, const char * alias,
		type_t type, const char * default_value) {
	if (TYPE_VALUE != type && TYPE_FLAG != type && TYPE_CONFIG != type) {
		throw exception("unknown configuration type");
	}

	for (string s : arguments_i::cast(_implementation)->_names) {
		if (s == string(name)) {
			stringstream ss;
			ss << "The name \"";
			ss << name;
			ss << "\" already exist.";
			throw exception(ss.str().c_str());
		}
	}

	arguments_i::cast(_implementation)->_names.push_back(name);

	if (arguments_i::cast(_implementation)->_aliases[alias] != "") {
		stringstream ss;
		ss << "The alias \"";
		ss << alias;
		ss << "\" already exist.";
		throw exception(ss.str().c_str());
	}

	arguments_i::cast(_implementation)->_aliases[alias] = name;
	arguments_i::cast(_implementation)->_types[name] = type;
	arguments_i::cast(_implementation)->_defaults[name] = default_value;
	return *this;
}

arguments & arguments::parse(int argc, char **argv) {
	// set defaults
	clean();

	// parse
	arguments_i::cast(_implementation)->_name = argv[0];
	vector<char *> args(argv + 1, argv + argc);
	int index = 0;
	for (vector<char *>::iterator i = args.begin(); i != args.end(); ++i) {
		string s = *i;
		if (0 == s.find(NAME_PREFIX)) {
			string name = s.substr(2);
			type_t type = arguments_i::cast(_implementation)->_types[name];
			if (0 == type) {
				arguments_i::cast(_implementation)->_errorsNames.push_back(s);
				arguments_i::cast(_implementation)->_errorsMessages.push_back(
						"Unknown argument");
			} else if (TYPE_FLAG == type) {
				arguments_i::cast(_implementation)->_values[name] = TRUE;
			} else {
				if (++i != args.end()) {
					arguments_i::cast(_implementation)->_values[name] = *i;
				} else {
					arguments_i::cast(_implementation)->_values[name] = NONE;
					--i;
				}
			}
		} else if (0 == s.find(ALIAS_PREFIX)) {
			string alias = s.substr(1);
			string name = arguments_i::cast(_implementation)->_aliases[alias];
			type_t type = arguments_i::cast(_implementation)->_types[name];
			if (0 == type) {
				arguments_i::cast(_implementation)->_errorsNames.push_back(s);
				arguments_i::cast(_implementation)->_errorsMessages.push_back(
						"Unknown argument");
			} else if (TYPE_FLAG == type) {
				arguments_i::cast(_implementation)->_values[name] = TRUE;
			} else {
				if (++i != args.end()) {
					arguments_i::cast(_implementation)->_values[name] = *i;
				} else {
					arguments_i::cast(_implementation)->_values[name] = NONE;
					--i;
				}
			}
		} else {
			// next index
			for (; index < arguments_i::cast(_implementation)->_names.size();
					++index) {
				string name =
						arguments_i::cast(_implementation)->_names[index];
				type_t type = arguments_i::cast(_implementation)->_types[name];
				if (TYPE_VALUE == type) {
					break;
				}
			}

			if (index >= arguments_i::cast(_implementation)->_names.size()) {
				arguments_i::cast(_implementation)->_errorsNames.push_back(s);
				arguments_i::cast(_implementation)->_errorsMessages.push_back(
						"Unknown argument");
			} else {
				string name =
						arguments_i::cast(_implementation)->_names[index];
				arguments_i::cast(_implementation)->_values[name] = s;
				++index;
			}
		}
	}
	return *this;
}

arguments & arguments::clean() {
	// set defaults
	arguments_i::cast(_implementation)->_name = "";
	for (string name : arguments_i::cast(_implementation)->_names) {
		arguments_i::cast(_implementation)->_values[name] =
				arguments_i::cast(_implementation)->_defaults[name];
	}

	// clean error message
	arguments_i::cast(_implementation)->_errorsNames.clear();
	arguments_i::cast(_implementation)->_errorsMessages.clear();

	return *this;
}

arguments & arguments::reset() {
	// set defaults
	clean();

	// reset configuration
	arguments_i::cast(_implementation)->_names.clear();
	arguments_i::cast(_implementation)->_types.clear();
	arguments_i::cast(_implementation)->_aliases.clear();
	arguments_i::cast(_implementation)->_defaults.clear();

	return *this;
}

const char * arguments::operator[](const char * name) const {
	return value(name);
}

const char * arguments::value(const char * name) const {
	return arguments_i::cast(_implementation)->_values[name].c_str();
}

const char * arguments::name() const {
	return arguments_i::cast(_implementation)->_name.c_str();
}

int arguments::errorSize() const {
	return arguments_i::cast(_implementation)->_errorsNames.size();
}
const char * arguments::errorName(int index) const {
	return arguments_i::cast(_implementation)->_errorsNames.at(index).c_str();
}
const char * arguments::errorMessage(int index) const {
	return arguments_i::cast(_implementation)->_errorsMessages.at(index).c_str();
}

} /* namespace pipe_ns */
