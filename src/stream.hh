#ifndef PIPE_STREAM_HH_
#define PIPE_STREAM_HH_

namespace pipe {

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

} /* namespace pipe */

#endif /* PIPE_STREAM_HH_ */
