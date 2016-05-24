#ifndef PIPE_NS_STREAM_HH_
#define PIPE_NS_STREAM_HH_

namespace pipe_ns {

class stream {
public:
	virtual ~stream();

	static stream * create(int buffer_size);
protected:
	stream();
private:
	stream(const stream &) = delete;
	stream & operator=(const stream &) = delete;
};

} /* namespace pipe_ns */

#endif /* PIPE_NS_STREAM_HH_ */
