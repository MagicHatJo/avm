#pragma once

#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <fstream>
#include <sstream>
#include "ThreadQueue.hpp"

//temp inc
#include <iostream>

#pragma region ENUMS
enum	e_command
{
	e_error,
	e_comment,
	e_push,
	e_pop,
	e_dump,
	e_assert,
	e_add,
	e_sub,
	e_mul,
	e_div,
	e_mod,
	e_print,
	e_exit
};

enum	e_operand//temp
{
	e_null,
	e_int8,
	e_int16,
	e_int32,
	e_float,
	e_double
};
#pragma endregion

#pragma region STRUCTS
typedef struct	s_token
{
	e_command	cmd;
	e_operand	type;
}				t_token;
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
	AbstractVM(const AbstractVM&);
	~AbstractVM(void);
	AbstractVM& operator = (const AbstractVM&);

	/* TEST */
	void	reader(void);
	void	lexer(void);
	void	parser(void);
};