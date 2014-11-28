#include "libbuf.h"

#define BUF_SIZE 16

char* read_from_buf(int fd) 
{

	char* buffer = (char*)malloc(BUF_SIZE * sizeof(char));
	char* result_str = NULL;
	int readed = 0;
	while((readed = read(fd, buffer, BUF_SIZE)) > 0) 
		{
			if (result_str == NULL) 
				{
					result_str = (char*)calloc(readed + sizeof(char), 1);
				} 
			else 
				{
					result_str = realloc(result_str, (strlen(result_str) + 1) * sizeof(char) + readed);
				}
			strncat(result_str, buffer, readed);
		}	
	if (readed < 0) 
		{
			printf("Can't read string\n");
			exit(-1);
		}

	free(buffer);

	return result_str;
}

void write_to_buf(char* str, int fd) 
{

	int i;
	for(i = 0; i < strlen(str); i++)
	{
		if (write(fd, str + i, 1) < 0) 
		{
			printf("Can't write a symbol\n");
			exit(-1);
		}
	}
}
