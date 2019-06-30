#pragma once

#include <string>
#include <iostream>
#include "eOperandType.hpp"
#include "IOperand.hpp"

template<typename T>
class Operand : public IOperand
{
private:
	eOperandType	_type;
	T				_value;
	std::string		_str;

public:
	Operand(void) : _type(e_null), _value(0), _str("") { }
	Operand<T>(eOperandType type, T val) : _type(type), _value(val), _str(std::to_string(val)) { }
	Operand<T>(const Operand<T> & val)
	{
		*this = val;
	}
	~Operand<T>(void) { }

	/* OVERLOADS */
	Operand<T>& operator = (Operand<T> const & val)//doesnt handle different types
	{
		if (this != &rhs)
		{
			this->_type = val.getType();
			this->_value = val.getValue();
			this->_str = std::to_string(val.getValue());
		}
		return (*this);
	}
	Operand& operator + (Operand const & val)
	{
		eOperandType	curType = (this->getType() > val.getType() ?
								   this->getType() : val.getType());
		double curNum = std::stod(val.toString());//check to see if double conversion needed, or can cast

		switch (curType)//maybe cast dynamic instead of switch case
		{
			case (e_int8)	:	
			case (e_int16)	:
			case (e_int32)	:
			case (e_float)	:
			case (e_double)	:
			default			:
		}
	}
	// Operand& operator - (Operand const & val)
	// {

	// }
	// Operand& operator * (Operand const & val)
	// {

	// }
	// Operand& operator / (Operand const & val)
	// {

	// }
	// Operand& operator % (Operand const & val)
	// {

	// }

	/* MEMBERS */
	eOperandType		getType(void)		const { return (_type); }
	int					getPrecision(void)	const { return (_type); }//static_cast<int> might be needed
	T					getValue(void)		const { return (_value);}
	std::string const &	toString(void)		const { return (_str);  }
};

template <class T>
std::ostream& operator << (std::ostream& os, const Operand<T>& opr)
{
	os << opr.toString();
	return (os);
}