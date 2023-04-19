#define _GNU_SOURCE

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

int ParentRoutine(char* nameF);
