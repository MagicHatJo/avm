

//new Operand<int8_t>(static_cast<int8_t>(std::stoi(val)))

/*
** TESTING OPERAND TEMPLATE
*/
#include <iostream>

#include "Operand.hpp"
#include "IOperand.hpp"
#include "eOperandType.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "needs 2 arguments" << std::endl;
        return (0);
    }

    Operand<int8_t> opr1(e_int8, std::stoi(av[1]));
    Operand<int8_t> opr2(e_int8, std::stod(av[2]));
    
    std::cout << "opr1 is: " << opr1 << std::endl;
    std::cout << "opr2 is: " << opr2 << std::endl;

    //std::cout << "add is: " << opt1 + opr2 << std::endl;

    return (0);
}