#pragma once

#include <map>
#include <string>

#include "eOperandType.hpp"

#include "IOperand.hpp"
#include "Operand.hpp"

typedef IOperand const * (*oprFunc)(std::string const &);

typedef struct	s_factMap : public std::map<eOperandType, oprFunc>
{
	s_factMap()
	{
		this->operator[](e_int8)   = OperandFactory::&createInt8;
		this->operator[](e_int16)  = OperandFactory::&createInt16;
		this->operator[](e_int32)  = OperandFactory::&createInt32;
		this->operator[](e_float)  = OperandFactory::&createFloat;
		this->operator[](e_double) = OperandFactory::&createDouble;
	};
}				t_factMap;

class OperandFactory
{
private:
	IOperand const * createInt8(std::string const &)	const;
	IOperand const * createInt16(std::string const &)	const;
	IOperand const * createInt32(std::string const &)	const;
	IOperand const * createFloat(std::string const &)	const;
	IOperand const * createDouble(std::string const &)	const;

public:
	OperandFactory(void);
	OperandFactory(const OperandFactory &);
	~OperandFactory(void);

	OperandFactory& operator = (const OperandFactory &);

	IOperand const * createOperand(eOperandType, std::string const &) const;
};