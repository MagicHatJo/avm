#pragma once

#include "IOperand.hpp"
#include <stdexcept>
#include <sstream>
#include <string>
#include <limits>

template <class T>
class Operand : public IOperand
{
private:
	T				_val;
	eOperandType	_type;
	std::string		_str;

public:
	Operand(void);
	Operand(T, eOperandType);
	Operand(const Operand&);
	virtual ~Operand(void);

	Operand &operator = (const Operand&);
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

std::ostream&	operator << (std::ostream& output, const IOperand& rhs);