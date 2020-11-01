#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token
{
        char type[20];
        char tkWord[20];
        int line;
} Token;

#endif

