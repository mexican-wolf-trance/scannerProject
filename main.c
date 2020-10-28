#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHARMAX 1024

int main(int argc, char *argv[])
{
	char *keywords[] = { "start", "stop", "iter", "void", "int", "exit", "scanf", "printf", "main", "if", "then", "let", "data", "func" };
	char pPos, *buffer, input[CHARMAX];
	FILE *fp;

	if (argc == 1 && !isatty(0))
	{
                printf("Incoming file from a pipe or some such!\n");
                buffer = malloc(CHARMAX * sizeof(char));
                while(fgets(buffer, CHARMAX - 1, stdin) != NULL)
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
	buffer = malloc(CHARMAX * sizeof(char));
	while (input[i] != NULL)
	{
		j = 0;
		buffer[k] = input[i];
		if (input[i] == '\n')
			line++;
		k++;
		while(j < 14)
		{
			if (strstr(buffer, keywords[j]) != NULL)
			{
				if (keywords[j] == "int")
				{
                        		if (input[i + 1] == 'f' && input[i - 3] == 'r' && input[i - 4] == 'p')
					{
						strcpy(buffer, "printf");
                                        	printf("KEYWORD %s FOUND ON LINE %d\n", buffer, line);
						memset(buffer, "\0", CHARMAX * sizeof(char) - 1);
						k = 0;
						break;
					}
				}
				strcpy(buffer, keywords[j]);
				printf("KEYWORD %s FOUND ON LINE %d\n", buffer, line);
				memset(buffer, "\0", CHARMAX * sizeof(char) - 1);
				k = 0;
				break;
			}
			j++;
		}
		i++;
	}
	free(buffer);

/*
	int j = 0, line = 0;
	while(keywords[j])
	{
		if (strstr(input, keywords[j]) != NULL)
		{
			printf("KEYWORD FOUND: %s\n", keywords[j]);
		}
		j++;
	}
*/
	printf("Done\n");

	return 0;
}
