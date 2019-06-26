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
	//maybe wait until parser is complete, without shutting it down, and join them
	//if 0 syntax errors, start factory and stack
	std::thread	thread_4(&AbstractVM::factory, &avm);
	std::thread	thread_5(&AbstractVM::execute, &avm);

	thread_1.join();
	thread_2.join();
	thread_3.join();
	thread_4.join();
	thread_5.join();

	return (0);
}