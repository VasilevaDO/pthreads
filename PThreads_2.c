#include "libbuf.h"


#define FILE1 "matrix.txt"
#define FILE2 "result.txt"

int n = 0;
int m = 0;
int* mtx1;
int* mtx2;
int* mtx3;

void matrix_product(int line, int column) 
{
	int i = 0;
	for(i = 0; i < n; i++) 
	{
		mtx3[ line * n + column ] += mtx1[ line * n + i ] * mtx2[ i * n + column ];
	}
}

void* pthread(void* id) 
{
	
	int thid = (int)id;

	int i = 0;
	while(thid + i * m < n * n) 
	{
		matrix_product((thid + i * m) / n, (thid + i * m) % n);
		i++;
	}
	return NULL;
}	

int main(int argc, char* argv[]) 
{

	if(argc < 2) 
	{
		printf("Can't get all arguments\n");
		exit(-1);
	}

	m = atoi(argv[1]);

	int fd = 0;
	if((fd = open(FILE1, O_RDONLY)) < 0) 
	{
		printf("Can't open a file\n");
		exit(-1);
	}

	char* str = 0;

	str = read_from_buf(fd);

	long int i;
	for(i = 0; i < strlen(str); i++) 
	{
		if (str[i] == ' ') 
		{
			n++;
		}
	}
	n /= 2;

	n = (int)sqrt(n);

	if(close(fd) < 0) printf("Can't close a file\n");

	int number = n * n;

	mtx1 = (int*)calloc(number, sizeof(int));
	mtx2 = (int*)calloc(number, sizeof(int));
	mtx3 = (int*)calloc(number, sizeof(int));

	int length = 0;
	int figure = 0;
	i = 0;
	for(length = 0; i < 2 * number; length++) 
	{
		if(str[length] == ' ') 
		{
			if(i < number) mtx1[i] = figure;
			if(i >= number) mtx2[i - number] = figure;
			figure = 0;
			i++;
			continue;
		}
		figure *= 10;
		figure += (str[length] - '0');
	}

	free(str);

	pthread_t* pthreads = (pthread_t*)calloc(m, sizeof(pthread_t));

	clock_t time = clock();

	for(i = 0; i < m; i++) 
	{
		if(pthread_create(pthreads + i, (pthread_attr_t *)NULL, pthread, (void*)i) > 0) 
		{
			printf("Can't creat a thread\n");
			exit(-1);
		}
	}

	for(i = 0; i < m; i++) 
	{
		if(pthread_join(pthreads[i], (void **)NULL) > 0) 
		{
			printf("Can't block a thread\n");
			exit(-1);
		}
	}

	time = clock() - time;

	if((fd = open(FILE2, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0) 
	{
		printf("Can't open a file-result\n");
		exit(-1);
	}
	
	write_to_buf("Product of matrixes:\n", fd);	

	for(i = 0; i < number; i++) 
	{

		char* number_char = (char*)calloc(1, sizeof(char));
		sprintf(number_char, "%d", mtx3[i]);

		write_to_buf(number_char, fd);
		write_to_buf(" ", fd);
		if((i + 1) % n == 0) write_to_buf("\n", fd);

		free(number_char);
	}

	write_to_buf("\nTime: ", fd);
		
	char* time_char = (char*)calloc(10, sizeof(char));
	sprintf(time_char, "%g", (double)time/CLOCKS_PER_SEC);

	write_to_buf(time_char, fd);

	free(time_char);

	if(close(fd) < 0) printf("Can't close a file-result\n");

	free(mtx1);
	free(mtx2);
	free(mtx3);

}
