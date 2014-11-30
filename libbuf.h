#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

char* read_from_buf(int fd);
void write_to_buf(char* str, int fd);
void itoa(int n, char s[]);
void reverse(char s[]);
void time_start(struct timeval * tv1, struct timezone * tz);
long time_stop(struct timeval * tv1, struct timeval * tv2, struct timeval * dtv, struct timezone * tz);