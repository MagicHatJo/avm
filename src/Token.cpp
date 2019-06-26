#include "Token.hpp"

#pragma region SETUP
Token::Token(void) : _cmd(e_error), _type(e_null), _value("") { }
Token::Token(const Token& cpy)
{
	this->_cmd = cpy.getCmd();
	this->_type = cpy.getType();
	this->_value = cpy.getValue();
}
Token::~Token(void) { }

Token& Token::operator = (const Token& old)
{
	this->_cmd = old.getCmd();
	this->_type = old.getType();
	this->_value = old.getValue();
	return (*this);
}
#pragma endregion

#pragma region SET
bool	Token::setCmd(std::string word)
{
	t_cmdMap	map;
	if ((this->_cmd = map[word]) == e_error)
		return (false);
	return (true);
}
bool	Token::setValue(std::string word)
{
	static const std::regex	re{"^(int8\\(|int16\\(|int32\\(|float\\(|double\\()+((-?\\d+\\.\\d+)|(-?\\d+))+\\)$"};
	std::smatch	match;
	t_oprMap	map;

	if (std::regex_match(word, match, re) && match.size() == 5)
	{
		this->_type = map[match[1]];
		this->_value = match[2];
		return (true);
	}
	return (false);
}
#pragma endregion

#pragma region GET
e_command	Token::getCmd(void)		const { return (_cmd);   }
e_operand	Token::getType(void)	const { return (_type);  }
std::string	Token::getValue(void)	const { return (_value); }
#pragma endregion

#pragma region UTIL
void	Token::resetToken(void)
{
	this->_cmd = e_error;
	this->_type = e_null;
	this->_value = "";
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
	return (true);
}
#pragma endregion