#include "AbstractVM.hpp"

#pragma region SETUP
AbstractVM::AbstractVM(void) : _fileName(nullptr) { }
AbstractVM::AbstractVM(std::string s) : _fileName(s) { }

AbstractVM::AbstractVM(const AbstractVM& cpy)
{
	//copy
}

AbstractVM::~AbstractVM(void) { }

AbstractVM& AbstractVM::operator = (const AbstractVM &old)
{
	(void)old;
	return (*this);
}
#pragma endregion

//reads a file line by line until end of file, passing 1 line at a time to lexer
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

//tokenizes the line, sends 1 at a time to parser
void	AbstractVM::lexer(void)
{
	std::string	line;

	while (_readToLex.isRunning() || !_readToLex.isEmpty())
	{
		_readToLex.pop(line);

		std::cout << line << std::endl;
		_lexToParse.push(line);
		// std::istringstream	ss(line);
		// while (ss)
		// {
		// 	std::string token;
		// 	ss >> token;
		// 	_lexToParse.push(token);
		// }
	}
	std::cout << "shutting down lexer\n";
	_lexToParse.shutdown();
}

void	AbstractVM::parser(void)
{
	std::string token;
	while (_lexToParse.isRunning() || !_lexToParse.isEmpty())
	{
		_lexToParse.pop(token);
		std::cout << "current token: |" << token << "|" << std::endl;
	}
	std::cout << "shutting down parser\n";
}