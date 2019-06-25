#pragma once

#pragma region INC
#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <fstream>
#include <sstream>

#include <string>

#include "ThreadQueue.hpp"
#include "Token.hpp"

//temp inc
#include <iostream>
#pragma endregion

#pragma region ENUMS
enum	e_state
{
	e_rror,
	e_cmd,
	e_type,
	e_limbo,
	e_newline,
	e_comment
};
#pragma endregion

class AbstractVM
{
private:
	std::string				_fileName;

	bool					_readerLoaded;
	std::mutex				_readerMutex;
	std::condition_variable	_readerCond;

	ThreadQueue<std::string>	_readToLex;
	ThreadQueue<std::string>	_lexToParse;

public:
	/* CANONICAL */
	AbstractVM(void);
	AbstractVM(std::string);
	AbstractVM(const AbstractVM &);
	~AbstractVM(void);
	AbstractVM& operator = (const AbstractVM &);

	/* THREADS */
	void	reader(void);
	void	lexer(void);
	void	parser(void);
	void	factory(void);
};