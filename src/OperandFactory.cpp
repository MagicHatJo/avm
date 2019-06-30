
#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void) { }
OperandFactory::OperandFactory(const OperandFactory & val) { }
OperandFactory::~OperandFactory(void) { }

OperandFactory& OperandFactory::operator = (const OperandFactory & val)
{

}

IOperand const * OperandFactory::createInt8(std::string const & val) const
{
	return (new Operand<int8_t>(static_cast<int8_t>(std::stoi(val))));
}

IOperand const * OperandFactory::createInt16(std::string const & val) const
{
	return (new Operand<int16_t>(static_cast<int16_t>(std::stoi(val))));
}

IOperand const * OperandFactory::createInt32(std::string const & val) const
{
	return (new Operand<int32_t>(static_cast<int32_t>(std::stoi(val))));
}

IOperand const * OperandFactory::createFloat(std::string const & val) const
{
	return (new Operand<float>(static_cast<float>(std::stof(val))));
}

IOperand const * OperandFactory::createDouble(std::string const & val) const
{
	return (new Operand<double>(static_cast<double>(std::stod(val))));
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & str) const
{
	t_factMap	map;
	return (map[type](str));
}