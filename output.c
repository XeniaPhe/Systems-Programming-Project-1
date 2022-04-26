#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "types.h"

FILE* file;

void openFile()
{
    file = fopen("output.txt","w+");
}

void insertLine(const char* line)
{    
    if(!file)
        promptError("Invalid File!");

    fprintf(file,"%s\n",line);
}

void closeFile()
{
    if(file)
    {
        fclose(file);
        file = NULL;
    }
}