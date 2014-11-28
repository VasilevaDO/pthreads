#include "libbuf.h"

#define MY_FILE "matrix.txt"

int main(int argc, char* argv[]) 
{

	if(argc < 2) 
	{
		printf("Can't get all arguments\n");
		exit(-1);
	}

	int fd = 0;
	
	if((fd = open(MY_FILE, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0) 
	{
		printf("Can't create a file\n");
		exit(-1);
	}

	srand(time(NULL));

	int i, j, n = 0;

	n = atoi(argv[1]);

	int number_int = 0;

	for(i = 0; i < 2 * n; i++) 
	{
		for(j = 0; j < n; j++) 
		{

			rand();
			number_int = rand() % 100;
			
			char* number_char = (char*)calloc(1, sizeof(char));
			sprintf(number_char, "%d", number_int);

			write_to_buf(number_char, fd);
			write_to_buf(" ", fd);

			free(number_char);
		}
	}

	if(close(fd) < 0) printf("Can't close a file\n");
	return 0;

}
