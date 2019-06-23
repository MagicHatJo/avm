#include <thread>
#include <iostream>

#include "AbstractVM.hpp"

int	main(int ac, char **av)
{
	if (ac > 2)
	{
		std::cout << "Print usage here" << std::endl;
		exit(0);
	}
	AbstractVM avm(ac == 2 ? av[1] : "");
	std::thread thread_1(&AbstractVM::reader, &avm);
	std::thread thread_2(&AbstractVM::lexer, &avm);
	std::thread	thread_3(&AbstractVM::parser, &avm);
	//factory
	//stack

	thread_1.join();
	thread_2.join();
	thread_3.join();

	return (0);
}