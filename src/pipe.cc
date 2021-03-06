#include <arguments.hh>
#include <config.h>
#include <endpoint.hh>
#include <pipe.hh>
#include <sys/signal.h>
#include <__mutex_base>
#include <future>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace pipe_ns {

class pipe_i: public pipe {
	arguments _args;
	endpoint *_endpoint_left;
	endpoint *_endpoint_right;
	std::promise<int> _promise;
public:
	pipe_i(const arguments &args);
	pipe_i(arguments &&args);

	virtual ~pipe_i();

	virtual int execute();

	void on_signal(int s);

private:
	pipe_i(const pipe_i &) = delete;
	pipe_i & operator=(const pipe_i &) = delete;
};

/*
 * the executing pipes
 */
std::vector<pipe_i *> pipes;
/*
 * record previous signal handler
 */
std::map<int, void (*)(int)> pre_signal_handlers;
/*
 * signal mutex
 */
std::mutex signal_mutex;
/*
 * the signal handler is registered
 */
bool signal_registered = false;

void signal_handler(int s) {

	for (pipe_i * p : pipes) {
		p->on_signal(s);
	}

	if (nullptr != pre_signal_handlers[s]) {
		pre_signal_handlers[s](s);
	}
}

pipe::pipe() {
}

pipe::~pipe() {
}

void print_name(std::stringstream &ss) {
	ss << PACKAGE << "-" << PACKAGE_VERSION << " (" << PACKAGE_BUGREPORT << ")"
			<< std::endl;
}

void print_usage(std::stringstream &ss) {
	ss << "Usage: pipe [options] <left_endpoint> <mode> <right_endpoint>"
			<< std::endl;

	ss << "\tleft_endpoint" << std::endl << "\t\t: the left end point for pipe."
			<< std::endl;

	ss << "\tright_endpoint" << std::endl
			<< "\t\t: the right end point for pipe." << std::endl;

	ss << "\tmode" << std::endl
			<< "\t\t: the value should be '/' for simplex or '//' for duplex."
			<< std::endl;

	ss << "Options:" << std::endl;

	ss << "\t-u, --upstream [-|+]<upstream>" << std::endl
			<< "\t\t: the upstream endpoint, the '+' is mirror, the '-' is capture, the default is mirror standard out."
			<< std::endl;

	ss << "\t-d, --downstream [-|+]<downstream>" << std::endl
			<< "\t\t: the downstream endpoint, the '+' is mirror, the '-' is capture, the default is mirror standard error."
			<< std::endl;

	ss << "Endpoint:" << std::endl;

	ss << "\t[^]<hostname>[:port]\t\t: tcp endpoint." << std::endl;

	ss << "\t=[hostname][:port]\t\t: tcp listen endpoint." << std::endl;

	ss << "\t@<filedescriptor>\t\t: I/O endpoint." << std::endl;

	ss << "\t%<filepath>\t\t\t: file path endpoint." << std::endl;
}

pipe * pipe::create(int argc, char *argv[]) {
	arguments args;

	args.configure("endpoint_l", "l", arguments::TYPE_VALUE);
	args.configure("mode", "m", arguments::TYPE_VALUE);
	args.configure("endpoint_r", "r", arguments::TYPE_VALUE);
	args.configure("upstream", "u", arguments::TYPE_CONFIG, "+@1");
	args.configure("downstream", "d", arguments::TYPE_CONFIG, "+@2");

	args.parse(argc, argv);

	std::stringstream ss;
	bool error = false;

	print_name(ss);

	if (args.errorSize()) {
		error = true;
		ss << "Errors:" << std::endl;
		for (int i = 0; i < args.errorSize(); ++i) {
			ss << "\t" << args.errorName(i) << "\t: " << args.errorMessage(i)
					<< "." << std::endl;
		}
	}

	if (std::string(args.NONE) != std::string(args["mode"])
			&& std::string("/") != std::string(args["mode"])
			&& std::string("//") != std::string(args["mode"])) {
		if (!error) {
			error = true;
			ss << "Errors:" << std::endl;
		}
		ss << "\t" << "the mode can not be '" << std::string(args["mode"])
				<< "'." << std::endl;
	}

	if (std::string(args.NONE) == std::string(args["endpoint_l"])
			|| std::string(args.NONE) == std::string(args["endpoint_r"])
			|| std::string(args.NONE) == std::string(args["mode"])) {
		error = true;
	}

	if (error) {
		print_usage(ss);
		throw exception(ss.str().c_str());
	}

	pipe * p = new pipe_i(std::move(args));

	return p;
}

pipe_i::pipe_i(const arguments &args) :
		_args(args), _endpoint_left(nullptr), _endpoint_right(nullptr), _promise() {
}

pipe_i::pipe_i(arguments &&args) :
		_args(std::move(args)), _endpoint_left(nullptr), _endpoint_right(
				nullptr), _promise() {
}

pipe_i::~pipe_i() {
	if (_endpoint_left) {
		delete _endpoint_left;
		_endpoint_left = nullptr;
	}
	if (_endpoint_right) {
		delete _endpoint_right;
		_endpoint_right = nullptr;
	}
}

int pipe_i::execute() {
	bool duplex = (std::string("//") != std::string(_args["mode"]));

	_endpoint_left = endpoint::create(_args["endpoint_l"], true);
	_endpoint_left = endpoint::create(_args["endpoint_r"], duplex);

	// TODO

	{
		std::lock_guard<std::mutex> lock(signal_mutex);
		if (!signal_registered) {
			signal_registered = true;

			// SIGHUP
			void (*pre_signal_handler)(int) = signal(SIGHUP, signal_handler);
			if (SIG_ERR == pre_signal_handler) {
				throw exception("error register signal handler for SIGHUP");
			} else {
				pre_signal_handlers[SIGHUP] = pre_signal_handler;
			}
			// SIGINT
			pre_signal_handler = signal(SIGINT, signal_handler);
			if (SIG_ERR == pre_signal_handler) {
				throw exception("error register signal handler for SIGINT");
			} else {
				pre_signal_handlers[SIGINT] = pre_signal_handler;
			}
			// SIGTERM
			pre_signal_handler = signal(SIGTERM, signal_handler);
			if (SIG_ERR == pre_signal_handler) {
				throw exception("error register signal handler for SIGTERM");
			} else {
				pre_signal_handlers[SIGTERM] = pre_signal_handler;
			}

			pipes.push_back(this);
		}
	}

	std::future<int> f = _promise.get_future();
	int s = f.get();

	// TODO release

	return 0;
}

void pipe_i::on_signal(int s) {
	_promise.set_value(s);
}

} /* namespace pipe_ns */
