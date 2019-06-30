

//new Operand<int8_t>(static_cast<int8_t>(std::stoi(val)))

/*
** TESTING OPERAND TEMPLATE
*/

#include "Operand.hpp"
#include "IOperand.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (0);


    IOperand const * opr1 = new Operand<int8_t>(e_int8, std::stoi(av[1]));
    
    
    return (0);
}