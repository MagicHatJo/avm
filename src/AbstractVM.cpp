#include "AbstractVM.hpp"

AbstractVM::AbstractVM(void) : _fileName(nullptr)
{
}
AbstractVM::AbstractVM(std::string s) : _fileName(s) { }

AbstractVM::AbstractVM(const AbstractVM& cpy)
{
	//copy
	(void)cpy;
}

AbstractVM::~AbstractVM(void) { }

AbstractVM& AbstractVM::operator = (const AbstractVM& old)
{
	(void)old;
	return (*this);
}

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
		line = "";
		_readToLex.pop(line);
		std::istringstream	ss(line);
		while (ss >> word)
		{
			_lexToParse.push(word);
		}
		_lexToParse.push("\n");
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
		try
		{
			_lexToParse.pop(word);
			if (word == "\n")
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
				case e_newline:	if (token.isEmpty())
									break;
								if (token.isValid() && !syntaxError)
									_parseToFact.push(token);
								else
									syntaxError++;
								token.resetToken();
								state = e_cmd;
								lineCount++;
								if (syntaxError)
								{
									syntaxError = 0;
									throw SyntaxException(lineCount - 1);
								}
								break;
				case e_comment:	std::cout << "Comment: " << word << std::endl;
								break;
				default:		throw SyntaxException();
			}
		}
		catch (std::exception& e)
		{
			std::cout << "\033[91mError:\033[0m " << e.what() << std::endl;
		}
		
	}
	_parseToFact.shutdown();
}

//factory
void	AbstractVM::factory(void)
{
	OperandFactory		factory;
	Token				token;

	//wait for priority until all syntax handling is complete??
	while (_parseToFact.isRunning() || !_parseToFact.isEmpty())
	{
		token.resetToken();
		_parseToFact.pop(token);

		if (token.getCmd() == e_push || token.getCmd() == e_assert)
		{
			_oprQueue.push(const_cast<IOperand*>(factory.createOperand(token.getType(), token.getValue())));
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
	e_command	order;

	while (_factToExe.isRunning() || !_factToExe.isEmpty())
	{
		order = e_error;
		_factToExe.pop(order);
		try
		{
			(this->*(_exe_map[order]))();
		}
		catch (std::exception& e)
		{
			std::cout << "\033[91mError:\033[0m " << e.what() << std::endl;
		}
	}
	//check to make sure exit was called
	if (order != e_exit)
		std::cout << "no exit found at end" << std::endl;
}

/******************** Overloads ********************/
std::ostream&	operator << (std::ostream& output, const IOperand& rhs)
{
	output << rhs.toString();
	return (output);
}


/******************** Exceptions ********************/
AbstractVM::SyntaxException::SyntaxException(void)
{
	std::ostringstream o;
	o << "Invalid syntax";
	_msg = o.str();
}
AbstractVM::SyntaxException::SyntaxException(int ln)
{
	std::ostringstream o;
	o << "Invalid syntax on line " << ln;
	_msg = o.str();
}
AbstractVM::SyntaxException::SyntaxException(const SyntaxException& cpy) { *this = cpy; }
AbstractVM::SyntaxException::~SyntaxException(void) throw() { }
AbstractVM::SyntaxException& AbstractVM::SyntaxException::operator = (const SyntaxException&) { return (*this); }
const char* AbstractVM::SyntaxException::what() const throw() { return (_msg.c_str()); }

AbstractVM::EmptyException::EmptyException(void) { }
AbstractVM::EmptyException::EmptyException(const EmptyException& cpy) { *this = cpy; }
AbstractVM::EmptyException::~EmptyException(void) throw() { }
AbstractVM::EmptyException& AbstractVM::EmptyException::operator = (const EmptyException&) { return (*this); }
const char* AbstractVM::EmptyException::what() const throw() { return ("Stack is empty"); }

AbstractVM::TypeException::TypeException(void) { }
AbstractVM::TypeException::TypeException(const TypeException& cpy) { *this = cpy; }
AbstractVM::TypeException::~TypeException(void) throw() { }
AbstractVM::TypeException& AbstractVM::TypeException::operator = (const TypeException&) { return (*this); }
const char* AbstractVM::TypeException::what() const throw() { return ("Operand type does not match"); }

AbstractVM::ValueException::ValueException(void) { }
AbstractVM::ValueException::ValueException(const ValueException& cpy) { *this = cpy; }
AbstractVM::ValueException::~ValueException(void) throw() { }
AbstractVM::ValueException& AbstractVM::ValueException::operator = (const ValueException&) { return (*this); }
const char* AbstractVM::ValueException::what() const throw() { return ("Operand value does not match"); }

AbstractVM::SizeException::SizeException(void) { }
AbstractVM::SizeException::SizeException(const SizeException& cpy) { *this = cpy; }
AbstractVM::SizeException::~SizeException(void) throw() { }
AbstractVM::SizeException& AbstractVM::SizeException::operator = (const SizeException&) { return (*this); }
const char* AbstractVM::SizeException::what() const throw() { return ("Stack does not have sufficient operands"); }