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
		if (write(fd, str + i, 1) < 1) 
		{
			printf("Can't write a symbol\n");
			exit(-1);
		}
	}
}

/* reverse:  переворачиваем строку s на месте */
void reverse(char s[])
{
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* записываем знак */
	n = -n;          /* делаем n положительным числом */
	i = 0;
	do 
	{       /* генерируем цифры в обратном порядке */
		s[i++] = n % 10 + '0';   /* берем следующую цифру */
	} while ((n /= 10) > 0);     /* удаляем */
	
	if (sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void time_start(struct timeval * tv1, struct timezone * tz)
{
	gettimeofday(tv1, tz);
}

long time_stop(struct timeval * tv1, struct timeval * tv2, struct timeval * dtv, struct timezone * tz)
{ 
	gettimeofday(tv2, tz);
	dtv->tv_sec = tv2->tv_sec - tv1->tv_sec;
	dtv->tv_usec = tv2->tv_usec - tv1->tv_usec;
	if(dtv->tv_usec<0) 
	{
		dtv->tv_sec--; 
		dtv->tv_usec += 1000000;
	}
	return dtv->tv_sec*1000 + dtv->tv_usec/1000;
}
