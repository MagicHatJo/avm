#pragma once

#include <map>
#include <string>
#include <regex>

#pragma region ENUMS
enum	e_command
{
	e_error,
	e_push,
	e_pop,
	e_dump,
	e_assert,
	e_add,
	e_sub,
	e_mul,
	e_div,
	e_mod,
	e_print,
	e_exit
};

enum	e_operand
{
	e_null,
	e_int8,
	e_int16,
	e_int32,
	e_float,
	e_double
};

typedef struct	s_cmdMap : public std::map<std::string, e_command>
{
	s_cmdMap()
	{
		this->operator[]("push")   = e_push;
		this->operator[]("pop")    = e_pop;
		this->operator[]("dump")   = e_dump;
		this->operator[]("assert") = e_assert;
		this->operator[]("add")    = e_add;
		this->operator[]("sub")    = e_sub;
		this->operator[]("mul")    = e_mul;
		this->operator[]("div")    = e_div;
		this->operator[]("mod")    = e_mod;
		this->operator[]("print")  = e_print;
		this->operator[]("exit")   = e_exit;
	};
}				t_cmdMap;

typedef struct	s_oprMap : public std::map<std::string, e_operand>
{
	s_oprMap()
	{
		this->operator[]("int8(")     = e_int8;
		this->operator[]("int16(")    = e_int16;
		this->operator[]("int32(")    = e_int32;
		this->operator[]("float(")    = e_float;
		this->operator[]("double(")   = e_double;
	};
}				t_oprMap;
#pragma endregion

class Token
{
private:
	e_command	_cmd;
	e_operand	_type;
	std::string	_value;

public:
	/* CANONICAL */
	Token(void);
	Token(const Token &);
	~Token(void);
	Token& operator = (const Token &);

	/* SET */
	bool	setCmd(std::string);
	bool	setValue(std::string);

	/* GET */
	e_command	getCmd(void)	const;
	e_operand	getType(void)	const;
	std::string	getValue(void)	const;

	/* UTIL */
	void	resetToken(void);
	bool	isValid(void);
};