#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void promptError(const char* errorMessage)
{
    fprintf(stderr,RED "[ERROR]" NC " : %s\n",errorMessage);
    exit(EXIT_FAILURE);
}