#pragma once

/*
* Enumeration of all Token type 
*/
enum class ETokenType
{
	END,
	NUMBER,
	ID,
	LEFT_PARE = '(',
	RIGHT_PARE = ')',
	PLUS = '+',
	MINUS = '-',
	MUL = '*',
	DIV = '/',
	ASSIGN = '='
};