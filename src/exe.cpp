
#include "AbstractVM.hpp"

void	AbstractVM::error_exe(void)
{
	std::cout << "error" << std::endl;
}

void	AbstractVM::push_exe(void)
{
	std::cout << "push" << std::endl;
	IOperand*	operand;

	_oprQueue.pop(operand);
	_theStack.push_back(operand);
}

void	AbstractVM::pop_exe(void)
{
	std::cout << "pop" << std::endl;
	if (_theStack.empty())
		throw std::runtime_error("Stack is empty");
	
	_theStack.pop_back();
}

void	AbstractVM::dump_exe(void)
{
	std::cout << "dump" << std::endl;
	for (size_t i = 0; i < _theStack.size(); i++)
		std::cout << _theStack[i]->toString() << std::endl;
}

void	AbstractVM::assert_exe(void)
{
	std::cout << "assert" << std::endl;
	IOperand*	operand;
	const IOperand*	top;

	_oprQueue.pop(operand);
	top = _theStack.front();
	
	if (operand->getType() != top->getType() ||
		operand->toString() != top->toString())
	{
		//throw error
		std::cout << "assert doesnt match" << std::endl;
	}
	else
	{
		std::cout << "assert matches" << std::endl;
	}
}

void	AbstractVM::add_exe(void)
{
	std::cout << "add" << std::endl;
	const IOperand* a;
	const IOperand* b;

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b + *a);
}

void	AbstractVM::sub_exe(void)
{
	std::cout << "sub" << std::endl;
	const IOperand* a;
	const IOperand* b;

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b - *a);
}

void	AbstractVM::mul_exe(void)
{
	std::cout << "mul" << std::endl;
	const IOperand* a;
	const IOperand* b;

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b * *a);
}

void	AbstractVM::div_exe(void)
{
	std::cout << "div" << std::endl;
	const IOperand* a;
	const IOperand* b;

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b / *a);
}

void	AbstractVM::mod_exe(void)
{
	std::cout << "mod" << std::endl;
	const IOperand* a;
	const IOperand* b;

	a = _theStack.back();
	_theStack.pop_back();
	b = _theStack.back();
	_theStack.pop_back();

	_theStack.push_back(*b % *a);
}

void	AbstractVM::print_exe(void)
{
	std::cout << "print" << std::endl;
	const IOperand*	top;

	top = _theStack.front();
	
	if (top->getType() != e_int32)
	{
		//throw error
		std::cout << "print doesnt match" << std::endl;
	}
	else
	{
		std::cout << "print matches" << std::endl;
		std::cout << static_cast<char>(std::stoi(top->toString())) << std::endl;
	}
}

void	AbstractVM::exit_exe(void)
{
	std::cout << "exit" << std::endl;
}