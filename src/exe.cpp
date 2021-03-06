
#include "AbstractVM.hpp"

void	AbstractVM::error_exe(void)
{
	throw SyntaxException();
}

void	AbstractVM::push_exe(void)
{
	IOperand*	operand;

	_oprQueue.pop(operand);
	_theStack.push_back(operand);
}

void	AbstractVM::pop_exe(void)
{
	if (_theStack.empty())
		throw EmptyException();
	_theStack.pop_back();
}

void	AbstractVM::dump_exe(void)
{
	for (size_t i = _theStack.size(); i > 0; i--)
		std::cout << _theStack[i - 1]->toString() << std::endl;
}

void	AbstractVM::assert_exe(void)
{
	IOperand*	operand;
	const IOperand*	top;

	if (_theStack.size() == 0)
		throw EmptyException();

	_oprQueue.pop(operand);
	top = _theStack.back();

	if (operand->getType() != top->getType())
		throw TypeException();
	if (operand->toString() != top->toString())
		throw ValueException();
}

void	AbstractVM::add_exe(void)
{
	const IOperand* a;
	const IOperand* b;

	if (_theStack.size() < 2)
		throw SizeException();

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b + *a);
}

void	AbstractVM::sub_exe(void)
{
	const IOperand* a;
	const IOperand* b;

	if (_theStack.size() < 2)
		throw SizeException();

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b - *a);
}

void	AbstractVM::mul_exe(void)
{
	const IOperand* a;
	const IOperand* b;

	if (_theStack.size() < 2)
		throw SizeException();

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b * *a);
}

void	AbstractVM::div_exe(void)
{
	const IOperand* a;
	const IOperand* b;

	if (_theStack.size() < 2)
		throw SizeException();

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b / *a);
}

void	AbstractVM::mod_exe(void)
{
	const IOperand* a;
	const IOperand* b;

	if (_theStack.size() < 2)
		throw SizeException();

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b % *a);
}

void	AbstractVM::print_exe(void)
{
	const IOperand*	top;

	if (_theStack.size() < 1)
		throw SizeException();

	top = _theStack.back();
	
	if (top->getType() != e_int8)
		throw TypeException();
	
	if (std::stoi(top->toString()) < 0 || std::stoi(top->toString()) > 127)
		throw ValueException();

	std::cout << static_cast<char>(std::stoi(top->toString())) << std::endl;
}

void	AbstractVM::exit_exe(void)
{
	_exitCalled = true;
}