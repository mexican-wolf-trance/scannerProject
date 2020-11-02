#ifndef TYPES_H
#define TYPES_H

#include <string.h>

char *keywords[] = { "start", "stop", "iter", "void", "int", "exit", "scanf", "printf", "main", "if","then", "let", "data", "func" };
char *operators[] = { "=", "=>", "=<", "==", ":", "+", "-", "*", "/", "%", ".", "(", ")", ",", "{", "}", ";", "[", "]" };
enum Types { KEYWORD, OPERATOR, NUMBER, IDENTIFIER };

char *idType(int x)
{
	static char idType[15];
	switch(x)
	{
		case 0:
			strcpy(idType, "KEYWORD");
			break;
		case 1:
			strcpy(idType, "OPERATOR");
			break;
		case 2:
			strcpy(idType, "NUMBER");
			break;
		case 3:
			strcpy(idType, "IDENTIFIER");
			break;
		default:
			strcpy(idType, "ERROR");
	}
	return idType;
}

#endif

