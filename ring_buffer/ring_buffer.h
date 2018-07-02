#ifndef SVEN_RING_BUFFER_H_
#define SVEN_RING_BUFFER_H_

#include <stdint.h>

namespace Sven
{
template <typename T , int MAXCOUNT>
class Ring_buffer
{
public:
	Ring_buffer() : head_(0), tail_(0) {};
	T *get();
	bool put(const T &data);
	bool empty() const { return head_ == tail_; }
	bool full() const { return (tail_ + 1) % (MAXCOUNT + 1) == head_; }
private:
	T buffer_[MAXCOUNT + 1];
	volatile uint32_t head_;
	volatile uint32_t tail_;
};

template <typename T, int MAXCOUNT>
T *Ring_buffer<T, MAXCOUNT>::get()
{
	if (empty()) return NULL;
	T *data = &buffer_[head_];
	head_ = (head_ + 1) % (MAXCOUNT + 1);
	return data;
}

template <typename T, int MAXCOUNT>
bool Ring_buffer<T, MAXCOUNT>::put(const T &data)
{
	if (full()) return false;

	buffer_[tail_] = data;
	tail_ = (tail_ + 1) % (MAXCOUNT + 1);

	return true;
}
}
#endif