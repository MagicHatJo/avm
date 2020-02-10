
#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void)
{
}
OperandFactory::OperandFactory(const OperandFactory & val)
{
	(void)val;
}
OperandFactory::~OperandFactory(void) { }

OperandFactory& OperandFactory::operator = (const OperandFactory & val)
{
	*this = val;
	return (*this);
}

IOperand const * OperandFactory::createInt8(std::string const& val) const
{
	return (new Operand<int8_t>(std::stoi(val), e_int8));
}

IOperand const * OperandFactory::createInt16(std::string const& val) const
{
	return (new Operand<int16_t>(std::stoi(val), e_int16));
}

IOperand const * OperandFactory::createInt32(std::string const& val) const
{
	return (new Operand<int32_t>(std::stoi(val), e_int32));
}

IOperand const * OperandFactory::createFloat(std::string const& val) const
{
	return (new Operand<float>(std::stof(val), e_float));
}

IOperand const * OperandFactory::createDouble(std::string const& val) const
{
	return (new Operand<double>(std::stod(val), e_double));
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const& str) const
{
	//try catch this
	return ((this->*(_map[type]))(str));
}