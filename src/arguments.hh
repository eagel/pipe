#ifndef PIPE_ARGUMENTS_HH_
#define PIPE_ARGUMENTS_HH_

namespace pipe {

class arguments {
	void * _implementation;
public:
	typedef int type_t;

	static constexpr const type_t TYPE_VALUE = 1;
	static constexpr const type_t TYPE_FLAG = 2;
	static constexpr const type_t TYPE_CONFIG = 3;

	static constexpr const char * const NAME_PREFIX = "--";
	static constexpr const char * const ALIAS_PREFIX = "-";

	static const char * const TRUE;
	static const char * const FALSE;
	static const char * const NONE;

	arguments();
	arguments(const arguments & args);
	arguments(arguments && args);
	~arguments();

	arguments & operator=(const arguments & args);
	arguments & operator=(arguments && args);

	arguments & configure(const char * name, const char * alias, type_t type);
	arguments & configure(const char * name, const char * alias, type_t type,
			const char * default_value);

	arguments & parse(int argc, char **argv);
	arguments & clean();
	arguments & reset();

	const char * operator[](const char * name) const;
	const char * value(const char * name) const;
	const char * name() const;

	int errorSize() const;
	const char * errorName(int index) const;
	const char * errorMessage(int index) const;
};

} /* namespace pipe */

#endif /* PIPE_ARGUMENTS_HH_ */
