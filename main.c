#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define INPUTMAX 102400
#define BUFFMAX 1024

typedef struct Token
{
	char type[20];
	char tkWord[20];
	int line;
} Token;

int main(int argc, char *argv[])
{
	char *keywords[] = { "start", "stop", "iter", "void", "int", "exit", "scanf", "printf", "main", "if", "then", "let", "data", "func" };
	char *operators[] = { "\"", "=", "=>", "=<", "==", ":", "+", "-", "*", "/", "%", ".", "(", ")", ",", "{", "}", ";", "[", "]" };
	char *types[] = { "keyword", "identifier", "operator", "number" };
	char pPos, *buffer, input[INPUTMAX];
	Token token = { .type = "", .tkWord = "", .line = 1 };
	FILE *fp;

	if (argc == 1 && !isatty(0))
	{
                printf("Incoming file from a pipe or some such!\n");
                buffer = malloc(INPUTMAX * sizeof(char));
                while(fgets(buffer, INPUTMAX - 1, stdin) != NULL)
                        strcat(input, buffer);
                printf("%s\n", input);
		free(buffer);
	}

	if (argc == 1 && isatty(0))
	{
		printf("If you have no arguments, you need to redirect a file!\nNo typing into the stdin with this one, buddy\n");
		return 0;
	}


        if (argc > 2)
        {
                printf("See readme for usage details\nThere should be at least one argument and no more\n");
                return 0;
        }

	if (argc == 2)
	{
		if ((pPos = strchr(argv[1], '.')) == NULL)
		{
        	        printf("Near as I can tell, you tried for an argument, but it wasn't a file\nEnter a file to be read into this program\n");
        	        return 0;
       		}
        	else
        	{
        	        printf("You wanted to open %s\n", argv[1]);
        	        fp = fopen(argv[1], "rb");
        	        if (fp == NULL)
                	{
                        	perror("Couldn't open this file. Are you sure its real?");
                        	return 0;
                	}
                	else
                	{
                	        fseek (fp, 0, SEEK_END);
                	        long length = ftell(fp);
                	        fseek (fp, 0, SEEK_SET);
                	        buffer = malloc(length);
                	        if(buffer != NULL)
                	                fread(buffer, 1, length, fp);
                	}
                	printf("Successfully read the contents of the file!\n");
                	fclose(fp);

	                strcpy(input, buffer);
        	        free(buffer);

			printf("%s\n", input);
        	}
	}

	int i = 0, j, k = 0, l = 0, line = 1;
	buffer = malloc(BUFFMAX * sizeof(char));
	memset(buffer, '\0', BUFFMAX * sizeof(char));
	while (input[i] != NULL)
	{
		if ((input[i] == '\n') || (input[i -1] && input[i - 1] == '\n'))
			token.line++;
		while (!isspace(input[i]))
		{
			buffer[k++] = input[i];
			//printf("buffer: %s\n", buffer);
			j = 0;
			while (j < 14)
			{
				if (strcmp(buffer, keywords[j]) == 0)
				{
					strcpy(token.type, "KEYWORD");
					strcpy(token.tkWord, buffer);
					printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
					memset(buffer, '\0', BUFFMAX * sizeof(char));
					k = 0;
					j = 0;
					break;
				}
				j++;
			}
			j = 0;
			if (input[i + 1] && ispunct(input[i + 1]) && isalnum(input[i]))
			{
				strcpy(token.type, "IDENTIFIER");
				strcpy(token.tkWord, buffer);
				printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
				memset(buffer, '\0', BUFFMAX * sizeof(char));
				k = 0;
				j = 0;
				break;
			}
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
                	       	        	                printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
                	               		                memset(buffer, '\0', BUFFMAX * sizeof(char));
                        	                       		k = 0;
                                	               		j = 0;
								break;
							}
                	                                if (input[i + 1] == '>')
                	                                {
                	                                        strcpy(token.type, "OPERATOR");
                	                                        strcpy(token.tkWord, "=>");
                	                                        printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
                	                                        memset(buffer, '\0', BUFFMAX * sizeof(char));
                	                                        k = 0;
                	                                        j = 0;
                	                                        break;
                	                                }
                        	                        if (input[i + 1] == '=')
                               		                {
                                	                        strcpy(token.type, "OPERATOR");
                                       		                strcpy(token.tkWord, "==");
                                                	        printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
                                                	        memset(buffer, '\0', BUFFMAX * sizeof(char));
                                                	        k = 0;
                                                	        j = 0;
                                                	       break;
                                                	}
						}
						strcpy(token.type, "OPERATOR");
						strcpy(token.tkWord, buffer);
						printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
						memset(buffer, '\0', BUFFMAX * sizeof(char));
						k = 0;
						j = 0;
						break;
					}
					j++;
				}
			}
			i++;
		}
		i++;
		if (buffer && (buffer[0] != '\0'))
		{
			strcpy(token.type, "IDENTIFIER");
			strcpy(token.tkWord, buffer);
			printf("%s %s found on line %d\n", token.type, token.tkWord, token.line);
			memset(buffer, '\0', BUFFMAX * sizeof(char));
			k = 0;
			j = 0;
		}
	}
	free(buffer);

	printf("Done\n");

	return 0;
}
