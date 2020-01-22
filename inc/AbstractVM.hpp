#pragma once

#pragma region INC
#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <queue>
#include <fstream>
#include <sstream>

#include <string>

#include "ThreadQueue.hpp"
#include "Token.hpp"

#include "IOperand.hpp"
#include "OperandFactory.hpp"

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

/* LOOKUP TABLE */
typedef struct	s_exeMap : public std::map<e_command>
{
	s_exeMap()
	{
		this->operator[](e_error)   = AbstractVM::&error_exe;
		this->operator[](e_push)    = AbstractVM::&push_exe;
		this->operator[](e_pop)     = AbstractVM::&pop_exe;
		this->operator[](e_dump)    = AbstractVM::&dump_exe;
		this->operator[](e_assert)  = AbstractVM::&assert_exe;
		this->operator[](e_add)     = AbstractVM::&add_exe;
		this->operator[](e_sub)     = AbstractVM::&sub_exe;
		this->operator[](e_mul)     = AbstractVM::&mul_exe;
		this->operator[](e_div)     = AbstractVM::&div_exe;
		this->operator[](e_mod)     = AbstractVM::&mod_exe;
		this->operator[](e_print)   = AbstractVM::&print_exe;
		this->operator[](e_exit)    = AbstractVM::&exit_exe;
	};
}				t_exeMap;

class AbstractVM
{
private:
	std::string				_fileName;

	ThreadQueue<std::string>	_readToLex;
	ThreadQueue<std::string>	_lexToParse;
	ThreadQueue<Token>			_parseToFact;
	ThreadQueue<e_command>		_factToExe;

	ThreadQueue<IOperand*>		_oprQueue;
	std::deque<IOperand*>		_theStack;

	t_exeMap	_exe_map;

	/* EXECUTE */
	void	error_exe(void);
	void	push_exe(void);
	void	pop_exe(void);
	void	dump_exe(void);
	void	assert_exe(void);
	void	add_exe(void);
	void	sub_exe(void);
	void	mul_exe(void);
	void	div_exe(void);
	void	mod_exe(void);
	void	print_exe(void);
	void	exit_exe(void);

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
	void	execute(void);
};