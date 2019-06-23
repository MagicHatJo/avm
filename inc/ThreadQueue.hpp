#pragma once

#include <mutex>
#include <queue>

template<typename T>
class ThreadQueue
{
private:
	std::queue<T>			_queue;
	std::mutex				_queue_mutex;
	std::condition_variable	_cond_var;

	volatile bool _isRunning;

public:
	ThreadQueue(void) : _queue(), _queue_mutex(), _cond_var(), _isRunning(true) { }
	ThreadQueue(const ThreadQueue & val) { *this = val; }
	~ThreadQueue(void) { }

	ThreadQueue operator = (const ThreadQueue & val)
	{
		(void)val;
		return (*this);
	}

	void	push(T const & val)
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);
		//bool to_notify = _queue.empty();
		_queue.push(val);
		lock.unlock();
		//if (to_notify)
		this->_cond_var.notify_one();
	}

	void	pop(T & val)
	{
		std::unique_lock<std::mutex> lock(_queue_mutex);
		while (_isRunning && _queue.empty())
			_cond_var.wait(lock);
		if (_queue.empty())
			return;
		val = _queue.front();
		_queue.pop();
	}

	bool	isRunning(void)
	{
		//std::unique_lock<std::mutex> lock(_queue_mutex);
		return (_isRunning);
	}
	bool	isEmpty(void)
	{
		//std::unique_lock<std::mutex> lock(_queue_mutex);
		return (_queue.empty());
	}
	void	shutdown(void)
	{
		//std::unique_lock<std::mutex> lock(_queue_mutex);
		_isRunning = false;
	}
};