#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "token.h"

#define BUFFMAX 1024

int scanner(char *input, struct Token token)
{
	int i = 0, j, k = 0;
        char *buffer = malloc(BUFFMAX * sizeof(char));
        memset(buffer, '\0', BUFFMAX * sizeof(char));
        while (input[i] != NULL)
        {
                if ((input[i] == '\n') || (input[i -1] && input[i - 1] == '\n'))
                        token.line++;
                while (!isspace(input[i]))
                {
                        buffer[k++] = input[i];
                        j = 0;
                        while (j < 14)
                        {
                                if (strcmp(buffer, keywords[j]) == 0)
                                {
                                        strcpy(token.type, "KEYWORD");
                                        strcpy(token.tkWord, buffer);
                                        printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                        memset(buffer, '\0', BUFFMAX * sizeof(char));
                                        k = 0;
                                        j = 0;
                                        break;
                                }
                                j++;
                        }
                        j = 0;
                        if (ispunct(input[i]))
                        {
                                while (j < 20)
                                {
                                        if (strcmp(buffer, operators[j]) == 0)
                                        {
                                                if (operators[j] == "=")
                                                {
                                                        if (input[i + 1] == '<')
                                                        {
                                                                strcpy(token.type, "OPERATOR");
                                                                strcpy(token.tkWord, "=<");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								memset(buffer, '\0', BUFFMAX * sizeof(char));
								k = 0;
                                                                j = 0;
                                                                i++;
                                                                break;
                                                        }
                                                        if (input[i + 1] == '>')
                                                        {
                                                                strcpy(token.type, "OPERATOR");
                                                                strcpy(token.tkWord, "=>");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								memset(buffer, '\0', BUFFMAX * sizeof(char));
								k = 0;
								j = 0;
								i++;
								break;
							}
                                                        if (input[i + 1] == '=')
                                                        {
                                                                strcpy(token.type, "OPERATOR");
                                                                strcpy(token.tkWord, "==");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                                                k = 0;
                                                                j = 0;
                                                                i++;
                                                               break;
                                                        }
						}
                                                strcpy(token.type, "OPERATOR");
                                                strcpy(token.tkWord, buffer);
                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                                k = 0;
                                                j = 0;
                                                break;
					}
					j++;
				}
			}
			if ((buffer[0] != '\0' && input[i + 1] && ispunct(input[i + 1]) && !isdigit(input[i])) || (buffer[0] != '\0' && ispunct(input[i]) && input[i + 1] && isalnum(input[i + 1])))
                        {
                                strcpy(token.type, "IDENTIFIER");
                                strcpy(token.tkWord, buffer);
                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                k = 0;
                                j = 0;
                                break;
                        }
			if (buffer[0] != '\0' && input[i + 1] && ispunct(input[i + 1]) && isdigit(input[i]))
			                        {
                                strcpy(token.type, "NUMBER");
                                strcpy(token.tkWord, buffer);
                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                k = 0;
                                j = 0;
                                break;
                        }
			i++;
		}
		i++;
                if (buffer && buffer[0] != '\0')
                {
                        strcpy(token.type, "IDENTIFIER");
                        strcpy(token.tkWord, buffer);
                        printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                        memset(buffer, '\0', BUFFMAX * sizeof(char));
                        k = 0;
                        j = 0;
                }
	}
	free(buffer);

	return 0;
}
