#ifndef TYPES_H
#define TYPES_H

char *keywords[] = { "start", "stop", "iter", "void", "int", "exit", "scanf", "printf", "main", "if","then", "let", "data", "func" };
char *operators[] = { "=", "=>", "=<", "==", ":", "+", "-", "*", "/", "%", ".", "(", ")", ",", "{", "", ";", "[", "]" };
enum Types { KEYWORD, OPERATOR, NUMBER, IDENTIFIER };

#endif

