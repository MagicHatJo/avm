#pragma once

#include <map>
#include <string>

#include "eOperandType.hpp"

#include "IOperand.hpp"
#include "Operand.hpp"

class OperandFactory
{
private:
	typedef IOperand const* (OperandFactory::*oprFunc)(std::string const &) const;

	IOperand const* createInt8(std::string const &)		const;
	IOperand const* createInt16(std::string const &)	const;
	IOperand const* createInt32(std::string const &)	const;
	IOperand const* createFloat(std::string const &)	const;
	IOperand const* createDouble(std::string const &)	const;

	oprFunc	_map[6] = {
		nullptr,
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	};

public:
	OperandFactory(void);
	OperandFactory(const OperandFactory &);
	~OperandFactory(void);

	OperandFactory& operator = (const OperandFactory &);

	IOperand const * createOperand(eOperandType type, std::string const& str) const;
};