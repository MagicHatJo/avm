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

class AbstractVM
{
private:
	std::string				_fileName;

	ThreadQueue<std::string>	_readToLex;
	ThreadQueue<std::string>	_lexToParse;
	ThreadQueue<Token>			_parseToFact;
	ThreadQueue<e_command>		_factToExe;

	ThreadQueue<IOperand*>		_oprQueue;

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