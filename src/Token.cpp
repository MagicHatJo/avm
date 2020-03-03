#include "Token.hpp"

Token::Token(void) : _cmd(e_error), _type(e_null), _value(""), _empty(true) { }
Token::Token(const Token& cpy)
{
	this->_cmd = cpy.getCmd();
	this->_type = cpy.getType();
	this->_value = cpy.getValue();
	this->_empty = cpy.isEmpty();
}
Token::~Token(void) { }

Token& Token::operator = (const Token& old)
{
	this->_cmd = old.getCmd();
	this->_type = old.getType();
	this->_value = old.getValue();
	this->_empty = old.isEmpty();
	return (*this);
}

bool	Token::setCmd(std::string word)
{
	t_cmdMap	map;

	this->_empty = false;
	if ((this->_cmd = map[word]) == e_error)
		return (false);
	return (true);
}
bool	Token::setValue(std::string word)
{
	static const std::regex	re{"^(int8\\(|int16\\(|int32\\(|float\\(|double\\()+((-?\\d+\\.\\d+)|(-?\\d+))+\\)$"};
	std::smatch	match;
	t_oprMap	map;

	this->_empty = false;
	if (std::regex_match(word, match, re) && match.size() == 5)
	{
		this->_type = map[match[1]];
		this->_value = match[2];
		return (true);
	}
	return (false);
}

e_command		Token::getCmd(void)		const { return (_cmd);   }
eOperandType	Token::getType(void)	const { return (_type);  }
std::string		Token::getValue(void)	const { return (_value); }
bool	Token::isEmpty(void)			const { return (_empty); }

void	Token::resetToken(void)
{
	this->_cmd = e_error;
	this->_type = e_null;
	this->_value = "";
	this->_empty = true;
}

bool	Token::isValid(void)
{
	if (this->_cmd == e_error)
		return (false);
	if (this->_cmd == e_push || this->_cmd == e_assert)
	{
		if (this->_type == e_null || this->_value == "")
			return (false);
	}
	else if (this->_type != e_null || this->_value != "")
		return (false);
	
	switch (this->_type)
	{
		case e_int8  :	if ((this->_value.find(".") != std::string::npos) ||
							std::stoi(this->_value) > std::numeric_limits<int8_t>::max() ||
							std::stoi(this->_value) < std::numeric_limits<int8_t>::min())
							return (false);
							break ;
		case e_int16 :	if ((this->_value.find(".") != std::string::npos) ||
							std::stoi(this->_value) > std::numeric_limits<int16_t>::max() ||
							std::stoi(this->_value) < std::numeric_limits<int16_t>::min())
							return (false);
							break ;
		case e_int32 :	if ((this->_value.find(".") != std::string::npos) ||
							std::stoi(this->_value) > std::numeric_limits<int32_t>::max() ||
							std::stoi(this->_value) < std::numeric_limits<int32_t>::min())
							return (false);
							break ;
		case e_float : return (true);
		case e_double: return (true);
		default: break;
	}

	return (true);
}