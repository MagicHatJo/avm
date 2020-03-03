#include "Operand.hpp"

template<class T> Operand<T>::Operand(void) { }

template<class T> Operand<T>::Operand(T val, eOperandType type) : _val(val), _type(type)
{
	_str = std::to_string(_val);
}

template<class T> Operand<T>::Operand(const Operand& cpy)
{
	this->_val = cpy.getVal(); 
	this->_type = cpy.getType();
	this->_str = cpy.toString();
}

template<class T> Operand<T>::~Operand() { }

template<class T> Operand<T>& Operand<T>::operator = (const Operand<T>& cpy)
{
	this->_val = cpy.getVal(); 
	this->_type = cpy.getType();
	this->_str = cpy.toString();
	return (*this);
}

template<class T> const IOperand* Operand<T>::operator + (const IOperand& rhs) const
{
	if(this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	
	T	rhs_val = static_cast<T>(std::stod(rhs.toString()));

	if (this->_val > 0 && rhs_val > 0 && static_cast<T>(this->_val + rhs_val) < rhs_val)
		throw std::overflow_error("Addition Overflow");
	if (this->_val < 0 && rhs_val < 0 && static_cast<T>(this->_val + rhs_val) > rhs_val)
		throw std::underflow_error("Addition Underflow");

	return new Operand<T>(this->_val + rhs_val, this->getType());
}

template<class T> const IOperand* Operand<T>::operator - (const IOperand& rhs) const
{
	double	rhs_val = std::stod(rhs.toString());

	if (this->getPrecision() < rhs.getPrecision())
	{
		switch (rhs.getPrecision())
		{
			case e_int16 :	if (rhs_val < 0 && this->_val > static_cast<int16_t>(std::numeric_limits<int16_t>::max() + rhs_val))
								throw std::overflow_error("Subtraction Overflow");
							if (rhs_val >= 0 && this->_val < static_cast<int16_t>(std::numeric_limits<int16_t>::min() + rhs_val))
								throw std::underflow_error("Subtraction Underflow");
							return new Operand<int16_t>(static_cast<int16_t>(this->_val) - rhs_val, rhs.getType());
			case e_int32 :	if (rhs_val < 0 && this->_val > static_cast<int32_t>(std::numeric_limits<int32_t>::max() + rhs_val))
								throw std::overflow_error("Subtraction Overflow");
							if (rhs_val >= 0 && this->_val < static_cast<int32_t>(std::numeric_limits<int32_t>::min() + rhs_val))
								throw std::underflow_error("Subtraction Underflow");
							return new Operand<int32_t>(static_cast<int32_t>(this->_val) - rhs_val, rhs.getType());
			case e_float :	if (rhs_val < 0 && this->_val > static_cast<float>(std::numeric_limits<float>::max() + rhs_val))
								throw std::overflow_error("Subtraction Overflow");
							if (rhs_val >= 0 && this->_val < static_cast<float>(-std::numeric_limits<float>::max() + rhs_val))
								throw std::underflow_error("Subtraction Underflow");
							return new Operand<float>(static_cast<float>(this->_val) - rhs_val, rhs.getType());
			case e_double:	if (rhs_val < 0 && this->_val > static_cast<double>(std::numeric_limits<double>::max() + rhs_val))
								throw std::overflow_error("Subtraction Overflow");
							if (rhs_val >= 0 && this->_val < static_cast<double>(-std::numeric_limits<double>::max() + rhs_val))
								throw std::underflow_error("Subtraction Underflow");
							return new Operand<double>(static_cast<double>(this->_val) - rhs_val, rhs.getType());
		}
	}

	if (rhs_val < 0 && this->_val > static_cast<T>(std::numeric_limits<T>::max() + rhs_val))
		throw std::overflow_error("Subtraction Overflow");
	if (this->getPrecision() <= e_int32)
	{
		if (rhs_val >= 0 && this->_val < static_cast<T>(std::numeric_limits<T>::min() + rhs_val))
			throw std::underflow_error("Subtraction Underflow");
	}
	else
	{
		if (rhs_val >= 0 && this->_val < static_cast<T>(-std::numeric_limits<T>::max() + rhs_val))
			throw std::underflow_error("Subtraction Underflow");
	}
	return new Operand<T>(this->_val - rhs_val, this->getType());
}

template<class T> const IOperand* Operand<T>::operator * (const IOperand& rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);

	T	rhs_val = static_cast<T>(std::stod(rhs.toString()));

	if ((rhs_val >= 0 && this->_val >= 0 && this->_val > std::numeric_limits<T>::max() / rhs_val)
		|| (rhs_val < 0 && this->_val < 0 && this->_val < std::numeric_limits<T>::max() / rhs_val))
		throw std::overflow_error("Multiplication Overflow");
	if ((rhs_val >= 0 && this->_val < 0 && this->_val < std::numeric_limits<T>::min() / rhs_val)
        || (rhs_val < 0 && this->_val >= 0 && this->_val > std::numeric_limits<T>::min() / rhs_val))
		throw std::underflow_error("Multiplication Underflow");

	return new Operand<T>(this->_val * rhs_val, this->getType());
}

template<class T> const IOperand* Operand<T>::operator / (const IOperand& rhs) const
{
	double	rhs_val = std::stod(rhs.toString());

	if (rhs_val == 0)
		throw std::invalid_argument("Division by 0");

	if (this->_val == std::numeric_limits<T>::min() && rhs_val == -1)
		throw std::overflow_error("Division Overflow");

	if (this->getPrecision() < rhs.getPrecision())
	{
		switch (rhs.getPrecision())
		{
			case e_int16 : return new Operand<int16_t>(static_cast<int16_t>(this->_val) / rhs_val, rhs.getType());
			case e_int32 : return new Operand<int32_t>(static_cast<int32_t>(this->_val) / rhs_val, rhs.getType());
			case e_float : return new Operand<float>(static_cast<float>(this->_val) / rhs_val, rhs.getType());
			case e_double: return new Operand<double>(static_cast<double>(this->_val) /rhs_val, rhs.getType());
		}
	}

	return new Operand<T>(this->_val / rhs_val, this->getType());
}

template<class T> const IOperand* Operand<T>::operator % (const IOperand& rhs) const
{
	int32_t	rhs_val = static_cast<int32_t>(std::stod(rhs.toString()));

	if (rhs_val == 0)
		throw std::invalid_argument("Mod by 0");
	if (this->getType() > e_int32 || rhs.getType() > e_int32)
		throw std::invalid_argument("Invalid Mod Type");
	if (this->_val == std::numeric_limits<T>::min() && rhs_val == -1)
		throw std::overflow_error("Division Overflow");

	if (this->getPrecision() < rhs.getPrecision())
	{
		switch (rhs.getPrecision())
		{
			case e_int16 : return new Operand<int16_t>(static_cast<int16_t>(this->_val) % rhs_val, rhs.getType());
			case e_int32 : return new Operand<int32_t>(static_cast<int32_t>(this->_val) % rhs_val, rhs.getType());
		}
	}

	return new Operand<int8_t>(static_cast<int8_t>(this->_val) % rhs_val, this->getType());
}

template<class T> bool Operand<T>::operator == (const IOperand& rhs) const
{
	if (this->_val == std::stod(rhs.toString()))
		return true;
	return false;
}

template<class T> T Operand<T>::getVal(void)				const { return (_val); }
template<class T> int Operand<T>::getPrecision(void)		const { return (_type); }
template<class T> eOperandType Operand<T>::getType(void)	const { return (_type); }

template<class T> std::string const& Operand<T>::toString(void)	const { return (_str); }

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;