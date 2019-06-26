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
	std::cout << "shutting down reader\n";
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

		while (ss >> word) //if there is a ; in the word, push until that, and then push that
		{
			_lexToParse.push(word);
		}
		_lexToParse.push("");
	}

	std::cout << "shutting down lexer\n";
	_lexToParse.shutdown();
}

void	AbstractVM::parser(void)
{
	std::string	word;
	Token		token;
	e_state		state = e_cmd;

	while (_lexToParse.isRunning() || !_lexToParse.isEmpty())
	{
		_lexToParse.pop(word);
		if (word == "")
			state = e_newline;
		else if (word.at(0) == ';')
			state = e_comment;
		switch (state)
		{
			case e_cmd:		token.setCmd(word);
							std::cout << "Cmd: " << token.getCmd() << std::endl;
							state = e_type;
							break;
			case e_type:	if (token.setValue(word))
								std::cout << "value set successfully\n";
							else
								std::cout << "set value failed\n";
							std::cout << "Type: " << token.getType() << std::endl;
							std::cout << "Value: " << token.getValue() << std::endl;
							state = e_limbo;
							break;
			case e_limbo:	std::cout << "Syntax error at end of line\n";
							break;
			case e_newline:	std::cout << "Checking token\n";
							//check token validity
							//push to factory if valid
							state = e_cmd;
							break;
			case e_comment:	std::cout << "Comment: " << word << std::endl;
							break;
			default:		std::cout << "syntax error\n";
		};
	}
	std::cout << "shutting down parser\n";
}

//factory
//dont start until parser is complete, to catch syntax errors?
//if it is an operand, push onto stack
//if it is an action, send action to stack thread to operate
void	AbstractVM::factory(void)
{
	
}
#pragma endregion