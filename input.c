#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "types.h"
#include "error.h"

static void flush()
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}

static void AddType(NumberType** types,int* size,NumberType type,int index)
{
    if(index==*size)
        (*types) = (NumberType*)realloc(*types,sizeof(NumberType)*(++(*size)));
    
    (*types)[index] = type; 
}

static Numbers getNumbers(const char* fileName)
{
    FILE* inputs = fopen(fileName,"r");

    if(inputs==NULL)
        promptError("Invalid File Name!");

    const char* invalidNumber = "Invalid Number!";
    const int defaultDigitCount=8;
    int digitCount=defaultDigitCount,digitIndex=0,type=999;   //0 for signed,1 for unsignes,2 for floating point
    char ch,*current = (char*)malloc(sizeof(char)*digitCount);

    int floatCount=1,floatIndex=0,intCount=1,intIndex=0,uintCount=1,uintIndex=0,totalCount=0;
    double *floats = (double*)malloc(sizeof(double)*floatCount);
    int *ints = (int*)malloc(sizeof(int)*intCount);
    unsigned int *uints = (unsigned int*)malloc(sizeof(unsigned int)*uintCount);
    NumberType *types = (NumberType*)malloc(sizeof(NumberType)*totalCount);

    while(ch = fgetc(inputs))
    {
        if(digitIndex==digitCount)
            current = (char*)realloc(current,(digitCount+=defaultDigitCount));
        
        if(ch == '\n' || ch == EOF)
        {
            current[digitIndex++] = '\0';
            current = (char*)realloc(current,digitIndex);

            switch (type)
            {
            case 0:

                if(intIndex==intCount)
                    ints = (int*)realloc(ints,++intCount);

                AddType(&types,&totalCount,Int,uintIndex+floatIndex+intIndex);

                ints[intIndex++] = strtol(current,NULL,10);

                break;
            case 1:

                if(uintIndex==uintCount)
                    uints = (unsigned int*)realloc(uints,++uintCount);

                AddType(&types,&totalCount,Uint,uintIndex+floatIndex+intIndex);

                uints[uintIndex++] = strtoul(current,NULL,10);

                break;
            case 2:

                if(floatIndex==floatCount)
                    floats = (double*)realloc(floats,++floatCount);

                AddType(&types,&totalCount,Float,uintIndex+floatIndex+intIndex);

                floats[floatIndex++] = strtod(current,NULL);

                break;
            }

            if(ch == EOF)
                break;
            
            current = (char*)realloc(current,(digitCount=defaultDigitCount));
            digitIndex=0;
            type=0;

            continue;
        }
        else if(ch == 'u' || ch == 'U')
        {
            if(type>0)
                promptError(invalidNumber);
            
            type = 1;
        }
        else if(ch == '.')
        {
            if(type>0)
                promptError(invalidNumber);

            type=2;
        }
        else if(ch == ',')
        {
            if(type>0)
                promptError(invalidNumber);

            ch = '.';
            type=2;
        }
        else if(ch == '-')
        {
            if(type>2)
                promptError("Invalid Number!");
        }
        else if(ch>='0' && ch<='9')
        {
            if(type>2)
                type=0;

            if(type==1)
                promptError(invalidNumber);
        }
        else
        {
            promptError(invalidNumber);
        }
        
        current[digitIndex++] = ch;
    }

    fclose(inputs);
    free(current);
    if(totalCount>uintCount+intCount+floatCount)
        types = (NumberType*)realloc(types,uintCount+intCount+floatCount);

    if(intCount!=intIndex)
    {
        free(ints);
        ints=NULL;
        intCount=0;
    }
    if(uintCount!=uintIndex)
    {
        free(uints);
        uints=NULL;
        uintCount=0;
    }
    if(floatCount!=floatIndex)
    {
        free(floats);
        floats=NULL;
        floatCount=0;
    }
    if(floatCount==0 && uintCount==0 && intCount==0)
    {
        free(types);
        types=NULL;
    }

    Numbers nums = {intCount,uintCount,floatCount,ints,uints,floats,types};

    return nums;
}

Numbers getInputs(ByteOrdering* byteordering,int* size)
{
    //Fetching file name and the Numbers from the file
    printf("Input File Name : ");    
    char* filename = (char*)malloc(sizeof(char)*261);  //Maximum path length in windows 10
    int ret = scanf("%s",filename);
    flush();    //To delete the newLine character from the buffer

    if(!(ret>0 && ret!=EOF))
        promptError("Invalid File Name!\n");
    filename = (char*)realloc(filename,strlen(filename));
    Numbers nums = getNumbers(filename);
    free(filename);
    
    //Getting the byte ordering from the user

    printf("Byte Ordering (l = Little Endian,b = Big Endian) : ");
    char byteOrder;
    ret = scanf("%c",&byteOrder);
    flush();

    if(!(ret>0 && ret!=EOF))
        promptError("Invalid File Name!\n");

    ByteOrdering ordering;

    if(byteOrder == 'l' || byteOrder =='L')
        ordering = littleEndian;
    else if(byteOrder == 'b' || byteOrder == 'B' )
        ordering = bigEndian;
    else
        promptError("Invalid Byte Ordering!");


    printf("Floating Point Size : ");
    int floatingPointSize = 0;
    ret = scanf("%d",&floatingPointSize);
    flush();
    printf("\n");

    if(!(ret>0 && ret!=EOF))
        promptError("Invalid File Name!\n");

    if(!(floatingPointSize > 0 && floatingPointSize < 5))
        promptError("Invalid Floating Point Size!");
    
    *byteordering = ordering;
    *size = floatingPointSize;
    return nums;
}