#include "AbstractVM.hpp"

#pragma region SETUP
AbstractVM::AbstractVM(void) : _fileName(nullptr) { }
AbstractVM::AbstractVM(std::string s) : _fileName(s) { }

AbstractVM::AbstractVM(const AbstractVM& cpy)
{
	//copy
}

AbstractVM::~AbstractVM(void) { }

AbstractVM& AbstractVM::operator = (const AbstractVM& old)
{
	(void)old;
	return (*this);
}
#pragma endregion

#pragma region AVM
void	AbstractVM::reader(void)
{
	std::string		line;
	if (_fileName.empty())
	{
		while (std::getline(std::cin, line) && line != ";;")
			_readToLex.push(line);
	}
	else
	{
		std::ifstream	ifs;
		ifs.open(_fileName);
		if (ifs.fail())
		{
			std::cout << "error, could not open file" << std::endl;
			exit(0);
		}
		while (std::getline(ifs, line))
			_readToLex.push(line);
	}
	_readToLex.shutdown();
}

void	AbstractVM::lexer(void)
{
	std::string	line;
	std::string	word;

	while (_readToLex.isRunning() || !_readToLex.isEmpty())
	{
		_readToLex.pop(line);
		std::istringstream	ss(line);
		while (ss >> word)
		{
			_lexToParse.push(word);
		}
		_lexToParse.push("");
	}
	_lexToParse.shutdown();
}

void	AbstractVM::parser(void)
{
	std::string	word;
	Token		token;
	e_state		state = e_cmd;
	int			syntaxError = 0;
	int			lineCount = 1;

	token.resetToken();
	while (_lexToParse.isRunning() || !_lexToParse.isEmpty())
	{
		_lexToParse.pop(word);
		if (word == "")
			state = e_newline;
		else if (word.at(0) == ';')
			state = e_comment;
		switch (state)
		{
			case e_cmd:		if (!(token.setCmd(word)))
								syntaxError++;
							state = e_type;
							break;
			case e_type:	if (!(token.setValue(word)))
								syntaxError++;
							state = e_limbo;
							break;
			case e_limbo:	syntaxError++;
							break;
			case e_newline:	if (token.isValid() && !syntaxError)
							{
								_parseToFact.push(token);
							}
							else
								std::cout << "Syntax error on line: " << lineCount << std::endl;
							token.resetToken();
							state = e_cmd;
							syntaxError = 0;
							lineCount++;
							break;
			case e_comment:	std::cout << "Comment: " << word << std::endl;
							break;
			default:		std::cout << "syntax error\n";
		};
	}
	_parseToFact.shutdown();
}

//factory
void	AbstractVM::factory(void)
{
	OperandFactory		factory;
	Token				token;
	const IOperand*		operand;

	//wait for priority until all syntax handling is complete??
	while (_parseToFact.isRunning() || !_parseToFact.isEmpty())
	{
		_parseToFact.pop(token);
		if (token.getCmd() == e_push || token.getCmd() == e_assert)
		{
			operand = factory.createOperand(token.getType(), token.getValue());
			//add to _oprQueue
		}
		_factToExe.push(token.getCmd());
	}
	_factToExe.shutdown();
}

//have queue of operands as well instead to avoid needing priority passing
//stack takes instructions and operates on the existing stack
//stops printing on first execution error
void	AbstractVM::execute(void)
{
	//std::vector<IOperand*>	theStack;
	e_command	order;

	while (_factToExe.isRunning() || !_factToExe.isEmpty())
	{
		_factToExe.pop(order);
		switch (order)
		{
			case (e_push)	:
			case (e_pop)	:
			case (e_dump)	:
			case (e_assert)	:
			case (e_add)	:
			case (e_sub)	:
			case (e_mul)	:
			case (e_div)	:
			case (e_mod)	:
			case (e_print)	:
			case (e_exit)	:
			default			: break ;
		};
	}
	//check to make sure exit was called
}
#pragma endregion