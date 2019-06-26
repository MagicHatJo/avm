#pragma once

#include <string>

template<typename T>
class Operand : public IOperand
{
private:
	eOperandType	_type;
	T				_value;

public:
	Operand(eOperandType type, T val) : _type(type), _value(val) { }
	Operand(const Operand & val) { }
	~Operand(void) { }

	Operand& operator = (Operand const & rhs)
	{
		_type = rhs.getType();
		_value = rhs.getValue();
	}
	Operand& operator + (Operand const & val)
	{
		//for all of these, check conversions, promote if needed, then operate
	}
	Operand& operator - (Operand const & val);
	Operand& operator * (Operand const & val);
	Operand& operator / (Operand const & val);
	Operand& operator % (Operand const & val);
	
	eOperandType		getType(void)		{ return (_type); }
	int					getPrecision(void)	{ return (_type); }//static_cast<int> might be needed
	T					getValue(void)		{ return (_value);}
	std::string const &	toString(void);		{ return (std::to_string(_value); }
};