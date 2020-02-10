#pragma once

#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <queue>
#include <fstream>
#include <sstream>

#include <string>

#include <vector>

#include "ThreadQueue.hpp"
#include "Token.hpp"

#include "IOperand.hpp"
#include "OperandFactory.hpp"

//temp inc
#include <iostream>

enum	e_state
{
	e_rror,
	e_cmd,
	e_type,
	e_limbo,
	e_newline,
	e_comment
};


class AbstractVM
{
private:
	std::string				_fileName;

	ThreadQueue<std::string>	_readToLex;
	ThreadQueue<std::string>	_lexToParse;
	ThreadQueue<Token>			_parseToFact;
	ThreadQueue<e_command>		_factToExe;

	ThreadQueue<IOperand*>			_oprQueue;
	std::vector<const IOperand*>	_theStack;

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

	typedef void (AbstractVM::*exeFunc)(void);

	exeFunc	_exe_map[12] = {
		&AbstractVM::error_exe,
		&AbstractVM::push_exe,
		&AbstractVM::pop_exe,
		&AbstractVM::dump_exe,
		&AbstractVM::assert_exe,
		&AbstractVM::add_exe,
		&AbstractVM::sub_exe,
		&AbstractVM::mul_exe,
		&AbstractVM::div_exe,
		&AbstractVM::mod_exe,
		&AbstractVM::print_exe,
		&AbstractVM::exit_exe
	};

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