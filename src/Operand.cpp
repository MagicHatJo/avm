#include "Operand.hpp"

#pragma region SETUP
template<class T> Operand<T>::Operand(void) { }

template<class T> Operand<T>::Operand(T val, eOperandType type) : _val(val), _type(type) { }

template<class T> Operand<T>::Operand(const Operand& cpy)
{
	_val = cpy.getVal();
	_type = cpy.getType();
}

template<class T> Operand<T>::~Operand() { }
#pragma endregion

#pragma region OVERLOAD
template<class T> const IOperand& Operand<T>::operator = (const Operand& cpy)
{
	_val = cpy.getVal(); 
	_type = cpy.getType();
	return (*this);
}

template<class T> const IOperand* Operand<T>::operator + (const IOperand& rhs) const
{
	if(this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	
	if (this->_val > 0 && rhs.getVal() > 0 && this->_val + rhs.getVal() < rhs.getVal()
		throw std::overflow_error("Addition Overflow");
	if (this->_val < 0 && rhs.getVal() < 0 && this->_val + rhs.getVal() > rhs.getVal())
		throw std::underflow_error("Addition Underflow");

	return new Operand<T>(this->_val + (static_cast<T>(rhs.getVal())), this->getType());
}

template<class T> const IOperand* Operand<T>::operator - (const IOperand& rhs) const
{
	//check for overflow or underflow
	if (this->getPrecision() < rhs.getPrecision())
		switch (rhs.getPrecision())
		{
			case e_int16: return new Operand<int16_t>(static_cast<int16_t>(this->_val) - rhs.getVal()), rhs->getType());
			case e_int16: return new Operand<int32_t>(static_cast<int32_t>(this->_val) - rhs.getVal()), rhs->getType());
			case e_int16: return new Operand<float>(static_cast<float>(this->_val) - rhs.getVal()), rhs->getType());
			case e_int16: return new Operand<double>(static_cast<double>(this->_val) - rhs.getVal()), rhs->getType());
		}
	return new Operand<T>(this->_val - (static_cast<T>(rhs.getVal())), this->getType());
}

template<class T> const IOperand* Operand<T>::operator * (const IOperand& rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);

	if (abs(this->_val) > std::numeric_limits<T>::max() / abs(rhs.getVal()))
	{
		if (this->_val > 0 && rhs.getVal() > 0 ||
			this->_val < 0 && rhs.getVal() < 0)
			throw std::overflow_error("Multiplication Overflow");
		if (this->val > 0 ^ rhs.getVal() > 0)
			throw std::underflow_error("Multiplication Underflow"); 
	}

	return new Operand<T>(this->_val * static_cast<T>(rhs.getVal()), this->getType());
}

template<class T> const IOperand* Operand<T>::operator / (const IOperand& rhs) const
{
	if (rhs.getVal() == 0)
		throw std::invalid_argument("Dividing by 0");

	if (this->getPrecision < rhs.getPrecision())
	{
		case e_int16 : return new Operand<int16_t>(static_cast<int16_t>(this->_val) / rhs.getVal()), rhs->getType());
		case e_int32 : return new Operand<int32_t>(static_cast<int32_t>(this->_val) / rhs.getVal()), rhs->getType());
		case e_float : return new Operand<float>(static_cast<float>(this->_val) / rhs.getVal()), rhs->getType());
		case e_double: return new Operand<double>(static_cast<double>(this->_val) / rhs.getVal()), rhs->getType());
	}

	return new Operand<T>(this->_val / (static_cast<T>(rhs.getVal())), this->getType())
}

template<class T> const IOperand* Operand<T>::operator % (const IOperand& rhs) const
{
	if (rhs.getVal() == 0)
		throw std::invalid_argument("Mod by 0");
	if (this->getType() > e_int32 || rhs.getType() > e_int32)
		throw std::invalid_argument("Invalid Mod Type")

	if (this->getPrecision < rhs.getPrecision())
	{
		case e_int16 : return new Operand<int16_t>(static_cast<int16_t>(this->_val) % rhs.getVal()), rhs->getType());
		case e_int32 : return new Operand<int32_t>(static_cast<int32_t>(this->_val) % rhs.getVal()), rhs->getType());
		case e_float : return new Operand<float>(static_cast<float>(this->_val) % rhs.getVal()), rhs->getType());
		case e_double: return new Operand<double>(static_cast<double>(this->_val) % rhs.getVal()), rhs->getType());
	}

	return new Operand<T>(this->_val % (static_cast<T>(rhs.getVal())), this->getType())
}

template<class T> bool Operand<T>::operator ==(const IOperand& rhs) const
{
	if (this->_val == rhs.getVal())
}
#pragma endregion

#pragma region GET
template<class T> T Operand<T>::getVal(void)				const { return (_val); }
template<class T> int Operand<T>::getPrecision(void)		const { return (_type); }
template<class T> eOperandType Operand<T>::getType(void)	const { return (_type); }
#pragma endregion

#pragma region STRING
template<class T> std::string const& Operand<T>::toString(void)	const { return std::to_string(_val); }
#pragma endregion

#pragma region HARD
template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
#pragma endregion