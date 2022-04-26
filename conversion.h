#include "types.h"

#ifndef CONVERSION_H
#define CONVERSION_H
char* intConversion(int intNum, ByteOrdering orderType);
char* unsignedIntConversion (unsigned int uintNum, ByteOrdering orderType);
char* floatconversion(double num,int byteSize,ByteOrdering orderType);
#endif