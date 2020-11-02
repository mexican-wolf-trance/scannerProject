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
	enum Types type;
	int i = 0, j, k = 0;
        char *buffer = malloc(BUFFMAX * sizeof(char));
	FILE *scannerFP;
        memset(buffer, '\0', BUFFMAX * sizeof(char));

	if ((scannerFP = fopen("log.out", "w")) == NULL)
	{
		perror("Failed to create the log\n");
		return 0;
	}
	else
	{
		printf("\nLog file successfully opened!\n");
		fprintf(scannerFP, "\n###################\nStart of scanner log file\n###################\n\n");
	}

        while (input[i] != NULL)
        {
                if ((input[i] == '\n') || (input[i -1] && input[i - 1] == '\n'))
                        token.line++;
		if (input[i] == '#')
		{
			while(input[i] != '\n')
				i++;
		}
                while (!isspace(input[i]))
                {
                        buffer[k++] = input[i];
                        j = 0;
                        while (j < 14)
                        {
                                if (strcmp(buffer, keywords[j]) == 0)
                                {
                                        strcpy(token.type, idType(type = KEYWORD));
                                        strcpy(token.tkWord, buffer);
                                        printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
					fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
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
						type = OPERATOR;
                                                if (operators[j] == "=")
                                                {
                                                        if (input[i + 1] == '<')
                                                        {
                                                                strcpy(token.type, idType(type));
                                                                strcpy(token.tkWord, "=<");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								memset(buffer, '\0', BUFFMAX * sizeof(char));
								k = 0;
                                                                j = 0;
                                                                i++;
                                                                break;
                                                        }
                                                        if (input[i + 1] == '>')
                                                        {
                                                                strcpy(token.type, idType(type));
                                                                strcpy(token.tkWord, "=>");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								memset(buffer, '\0', BUFFMAX * sizeof(char));
								k = 0;
								j = 0;
								i++;
								break;
							}
                                                        if (input[i + 1] == '=')
                                                        {
                                                                strcpy(token.type, idType(type));
                                                                strcpy(token.tkWord, "==");
                                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
								fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                                                k = 0;
                                                                j = 0;
                                                                i++;
                                                               break;
                                                        }
						}
                                                strcpy(token.type, idType(type));
                                                strcpy(token.tkWord, buffer);
                                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
						fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
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
				if (ispunct(input[i]))
				{
					strcpy(token.type, idType(type = 100));
					strcpy(token.tkWord, buffer);
					printf("LEXICAL %s: %s on line %d is not an operator\n", token.type, token.tkWord, token.line);
					fprintf(scannerFP, "LEXICAL %s: %s on line %d is not an operator\n", token.type, token.tkWord, token.line);
					memset(buffer, '\0', BUFFMAX * sizeof(char));
					k = 0;
					j = 0;
					break;
				}
        	                if (isupper(input[i]) || isdigit(input[i]))
        	                {
					printf("This one\n");
        	                      	strcpy(token.type, idType(type = 100));
        	                       	strcpy(token.tkWord, buffer);
        	                       	printf("LEXICAL %s: %s on line %d is not a proper identifier\n", token.type, token.tkWord, token.line);
        	                       	fprintf(scannerFP, "LEXICAL %s: %s on line %d is not a proper identifier\n", token.type, token.tkWord, token.line);
        	                       	memset(buffer, '\0', BUFFMAX * sizeof(char));
        	                        k = 0;
        	                        j = 0;
					break;
	                        }
                                strcpy(token.type, idType(type = IDENTIFIER));
                                strcpy(token.tkWord, buffer);
				fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                k = 0;
                                j = 0;
                                break;
                        }
			if (buffer[0] != '\0' && input[i + 1] && ispunct(input[i + 1]) && isdigit(input[i]))
			{
                                strcpy(token.type, idType(type = NUMBER));
                                strcpy(token.tkWord, buffer);
                                printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
				fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
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
			if (isupper(buffer[0]) || isdigit(buffer[0]))
			{
                                        if (isdigit(buffer[0]))
                                        {
						int b = 0;
                                                while ((buffer[b]) != '\0')
                                                {
                                                        if (isalpha(buffer[i]) && ispunct(buffer[i]))
                                                        {
                                                                type = 100;
                                                                break;
                                                        }
							b++;
                                                }
                                        }
                                        if (type == 100)
                                        {
                                                strcpy(token.type, idType(type));
                                                strcpy(token.tkWord, buffer);
                                                printf("LEXICAL %s: %s on line %d is not a proper identifier\n", token.type, token.tkWord, token.line);
                                                fprintf(scannerFP, "LEXICAL %s: %s on line %d is not a proper identifier\n", token.type, token.tkWord, token.line);
                                                memset(buffer, '\0', BUFFMAX * sizeof(char));
                                                k = 0;
                                                j = 0;
                                        }
					else
					{
                                        	strcpy(token.type, idType(type = NUMBER));
                                        	strcpy(token.tkWord, buffer);
                                        	printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                                        	fprintf(scannerFP, "%s %s found on line %d\n", token.type, token.tkWord, token.line);
                                        	memset(buffer, '\0', BUFFMAX * sizeof(char));
                                        	k = 0;
                                        	j = 0;
					}

			}
			else
			{
                        	strcpy(token.type, idType(type = IDENTIFIER));
                        	strcpy(token.tkWord, buffer);
                        	printf("%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
				fprintf(scannerFP, "%s \"%s\" found on line %d\n", token.type, token.tkWord, token.line);
                        	memset(buffer, '\0', BUFFMAX * sizeof(char));
                        	k = 0;
                        	j = 0;
			}
                }
	}
	free(buffer);

	return 0;
}
