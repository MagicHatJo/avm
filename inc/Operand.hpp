#pragma once

#include "IOperand.hpp"
#include <stdexcept>
#include <sstream>
#include <string>

template <class T>
class Operand : public IOperand
{
private:
	T				_val;
	eOperandType	_type;

public:
	Operand(void);
	Operand(T, eOperandType);
	Operand(const Operand&);
	virtual ~Operand(void);

	IOperand const& operator = (const Operand&);
	IOperand const* operator + (const IOperand&) const;
	IOperand const* operator - (const IOperand&) const;
	IOperand const* operator * (const IOperand&) const;
	IOperand const* operator / (const IOperand&) const;
	IOperand const* operator % (const IOperand&) const;
	bool            operator ==(const IOperand&) const;

	T				getVal(void)		const;
	int				getPrecision(void)	const;
	eOperandType	getType(void)		const;

	std::string const& toString(void) const;
};

std::ostream&	operator << (std::ostream& output, const Operand& rhs);