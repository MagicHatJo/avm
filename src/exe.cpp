
#include "AbstractVM.hpp"

void	AbstractVM::push_exe(void)
{
	IOperand**	operand;

	_oprQueue.pop(&operand);
	_theStack.push_front(*operand);
}

void	AbstractVM::pop_exe(void)
{
	if (_theStack.empty())
		throw std::runtime_error("Stack is empty");
	
	_theStack.pop_front();
}

void	AbstractVM::dump_exe(void)
{
	//std::deque<IOperand*>		_theStack;
	//go through stack, print each item
	std::for_each(
		_theStack.begin(),
		_theStack.end(),
		[](int const& i)
		{
			std::cout << i << std::endl;
		})
}

void	AbstractVM::assert_exe(void)
{
	//pop top value of oprqueue
	IOperand*	operand;
	IOperand*	top;

	_oprQueue.pop(operand);
	top = _theStack.front();
	
	if (operand == top)
	{
		//validate
	}
	//else throw error
}

void	AbstractVM::add_exe(void)
{

}

void	AbstractVM::sub_exe(void)
{

}

void	AbstractVM::mul_exe(void)
{

}

void	AbstractVM::div_exe(void)
{

}

void	AbstractVM::mod_exe(void)
{

}

void	AbstractVM::print_exe(void)
{

}

void	AbstractVM::exit_exe(void)
{

}