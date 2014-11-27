#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

char* read_buf(int fd);
void write_buf(char* str, int fd);
