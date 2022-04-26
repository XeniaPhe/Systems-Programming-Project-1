#include <stdlib.h>
#include <stdio.h>
#include "types.h"

static int power(int base,int pow)
{
    if(pow==0)
        return 1;

    if(pow%2==0)
        return power(base,pow/2)*power(base,pow/2);
    else
        return base*power(base,pow/2)*power(base,pow/2);
}

char* intConversion(int intNum, ByteOrdering orderType){
    bool isNegative = false;
    int totalBinaryBits = 16;


    if(intNum<0){
        isNegative = true;
        intNum =  intNum*(-1);
    }
    
    char binary [totalBinaryBits];
    int index = 0;
    int tempBits = totalBinaryBits;
    while (tempBits>0){
        while(intNum>0){
            if(intNum % 2 == 0){
                binary[index] = '0';

            }else{
                binary[index] = '1';

            }

            intNum = intNum / 2;
            index++;
            tempBits--;
        }
        binary[index] = '0';
        index++;
        tempBits--;
    }

    char revBinary[totalBinaryBits];
    int ind = 0;
    for(int i = totalBinaryBits-1; i>=0; i--){
        revBinary[ind] = binary[i];
        ind++;
    }

    char onesComplement[totalBinaryBits];
    char twosComplement[totalBinaryBits];
    int carry = 1;


    if(isNegative == true){
        for(int i=0;i<totalBinaryBits-1;i++)
        {
            if(revBinary[i]=='0')
                onesComplement[i]='1';
            else if(revBinary[i]=='1')
                onesComplement[i]='0';
        }
        onesComplement[totalBinaryBits-1]='\0';

        for(int i=totalBinaryBits-2; i>=0; i--)
        {
            if(onesComplement[i] == '1' && carry == 1)
            {
                twosComplement[i] = '0';
            }
            else if(onesComplement[i] == '0' && carry == 1)
            {
                twosComplement[i] = '1';
                carry = 0;
            }
            else
            {
                twosComplement[i] = onesComplement[i];
            }
        }
        twosComplement[totalBinaryBits-1]='\0';
    }else{
        int ind = 0;
        for(int i = totalBinaryBits-1; i>=0; i--){

            twosComplement[i] = binary[i];
            ind++;
        }
    }

    char revTwosComplement[totalBinaryBits];
    int nInd = 0;
    for(int i = totalBinaryBits-1; i>=0; i--){
 
        revTwosComplement[nInd] = twosComplement[i];
        nInd++;
    }


    char hex[4];
    int sum = 0;
    int ind2 = 0;

    for(int i = 0; i<totalBinaryBits; i++){

        if(twosComplement[i] == '1'){
            sum = sum + power(2, i%4);
        }

        if( (i % 4 == 3) || i == 15){
            switch (sum) {
                case 0:
                    hex[ind2] = '0';
                    break;
                case 1:
                    hex[ind2] = '1';
                    break;
                case 2:
                    hex[ind2] = '2';
                    break;
                case 3:
                    hex[ind2] = '3';
                    break;
                case 4:
                    hex[ind2] = '4';
                    break;
                case 5:
                    hex[ind2] = '5';
                    break;
                case 6:
                    hex[ind2] = '6';
                    break;
                case 7:
                    hex[ind2] = '7';
                    break;
                case 8:
                    hex[ind2] = '8';
                    break;
                case 9:
                    hex[ind2] = '9';
                    break;
                case 10:
                    hex[ind2] = 'A';
                    break;
                case 11:
                    hex[ind2] = 'B';
                    break;
                case 12:
                    hex[ind2] = 'C';
                    break;
                case 13:
                    hex[ind2] = 'D';
                    break;
                case 14:
                    hex[ind2] = 'E';
                    break;
                case 15:
                    hex[ind2] = 'F';
                    break;
            }
            ind2++;
            sum = 0;
        }

    }

    char revHex[6];
    revHex[0] = '0';
    revHex[1] = 'x';
    int ind3 = 2;
    for(int i = 3; i>=0; i--){
        revHex[ind3] = hex[i];
        ind3++;
    }
    

    if(orderType == littleEndian)
    {
        char *little = (char*)malloc(sizeof(char)*6);
        little[0] = revHex[4];
        little[1] = revHex[5];
        little[2] = ' ';
        little[3] = revHex[2];
        little[4] = revHex[3];
        little[5] = '\0';

        return little;

    }

    char *big = (char*)malloc(sizeof(char)*6);
    big[0] = revHex[2];
    big[1] = revHex[3];
    big[2] = ' ';
    big[3] = revHex[4];
    big[4] = revHex[5];
    big[5] = '\0';

    return big;
}

char* unsignedIntConversion (unsigned int uintNum, ByteOrdering orderType){
    int totalBinaryBits = 16;

    // convert to binary

    char binary [totalBinaryBits];
    int index = 0;
    int tempBits = totalBinaryBits;
    while (tempBits>0){
        while(uintNum>0){
            if(uintNum % 2 == 0){
                binary[index] = '0';

            }else{
                binary[index] = '1';

            }

            uintNum = uintNum / 2;
            index++;
            tempBits--;
        }
        binary[index] = '0';
        index++;
        tempBits--;
    }
    char revBinary[totalBinaryBits];
    int ind = 0;
    for(int i = totalBinaryBits-1; i>=0; i--){
        revBinary[ind] = binary[i];
        ind++;
    }

    // binary to hex

    char hex[4];
    int sum = 0;
    int ind2 = 0;

    for(int i = 0; i<totalBinaryBits; i++){

        if(binary[i] == '1'){
            sum = sum + power(2, i%4);
        }

        if( (i % 4 == 3) || i == 15){
            switch (sum) {
                case 0:
                    hex[ind2] = '0';
                    break;
                case 1:
                    hex[ind2] = '1';
                    break;
                case 2:
                    hex[ind2] = '2';
                    break;
                case 3:
                    hex[ind2] = '3';
                    break;
                case 4:
                    hex[ind2] = '4';
                    break;
                case 5:
                    hex[ind2] = '5';
                    break;
                case 6:
                    hex[ind2] = '6';
                    break;
                case 7:
                    hex[ind2] = '7';
                    break;
                case 8:
                    hex[ind2] = '8';
                    break;
                case 9:
                    hex[ind2] = '9';
                    break;
                case 10:
                    hex[ind2] = 'A';
                    break;
                case 11:
                    hex[ind2] = 'B';
                    break;
                case 12:
                    hex[ind2] = 'C';
                    break;
                case 13:
                    hex[ind2] = 'D';
                    break;
                case 14:
                    hex[ind2] = 'E';
                    break;
                case 15:
                    hex[ind2] = 'F';
                    break;
            }
            ind2++;
            sum = 0;
        }

    }


    char revHex[6];
    revHex[0] = '0';
    revHex[1] = 'x';
    int ind3 = 2;
    for(int i = 3; i>=0; i--){
        revHex[ind3] = hex[i];
        ind3++;
    }

    // hex to endian

    if(orderType == littleEndian)
    {
        char *little = (char*)malloc(sizeof(char)*6);
        little[0] = revHex[4];
        little[1] = revHex[5];
        little[2] = ' ';
        little[3] = revHex[2];
        little[4] = revHex[3];
        little[5] = '\0';

        return little;

    }

    char *big = (char*)malloc(sizeof(char)*6);
    big[0] = revHex[2];
    big[1] = revHex[3];
    big[2] = ' ';
    big[3] = revHex[4];
    big[4] = revHex[5];
    big[5] = '\0';

    return big;

}

static int returnExponent(int n){
    int rem;
    int p=0;
    int binaryInt=0;
    
    while (n!=0)
    {
        rem = n % 2;
        binaryInt=binaryInt+rem*power(10,p);
        n=n/2;
        p++;
    }

    return p-1;
}

char* floatconversion(double num,int byteSize,ByteOrdering orderType){
    
    int totalBinaryBits,exponentBits;
    int intpart;
    double fractPart;
    
    if (byteSize==1)
    {
        totalBinaryBits=8;  
        exponentBits=3;
    }
    else if(byteSize==2){
        totalBinaryBits=16;
        exponentBits=8;
    }
    else if(byteSize==3){
        totalBinaryBits=24;
        exponentBits=10;
    }
    else if(byteSize==4){
        totalBinaryBits=32;
        exponentBits=12;
    }
    
    int mantissaBits=totalBinaryBits-exponentBits-1;
    int fractionBits=mantissaBits;
    intpart=(int)num;
    fractPart=num-intpart;

    int E=returnExponent(intpart);
    int exp=E+127;

    char binary[totalBinaryBits];
    char mantissa[23];
    char exponent[exponentBits];
    char signbit;

    if (num >=0)
        signbit= '0';
    else
    {
        signbit= '1';
        num=-(num);
    }

    int index1 = 0;
    int tempBits1 = exponentBits;    

    while (tempBits1>0){
        while(exp>0){
            if(exp % 2 == 0){
                exponent[index1] = '0';

            }else{
                exponent[index1] = '1';

            }

            exp = exp / 2;
            index1++;
            tempBits1--;
        }
        exponent[index1] = '0';
        index1++;
        tempBits1--;
    }

    int index2 =0;
    int tempBits2=23;
    int intbitcount=0;
    int floatbitcount=0;
    while (tempBits2>0){
        
        while (intpart>0){
            if (intpart % 2==0)
            {
                mantissa[index2] = '0';
                intbitcount++;
            }else{
                mantissa[index2] = '1';
                intbitcount++;
            }
            intpart = intpart/2;
            index2++;
            tempBits2--;
        }
        while (fractPart!=0.0){
    
            fractPart=fractPart*2.0;
            
            int fract_bit=(int)fractPart;
            if (fract_bit==1)
            {
                mantissa[index2]='1';
                floatbitcount++;
            }
            else if(fract_bit==0){
                mantissa[index2]='0';
                floatbitcount++;
            }
            fractPart=fractPart-fract_bit;
            index2++;
            tempBits2--;
        }
        mantissa[index2]= '0';
        index2++;
        tempBits2--;
    }

    char reversemantissa[intbitcount+floatbitcount];
    int reversindex=0;
    for (int i = intbitcount-1; i >= 0; i--){
        reversemantissa[reversindex]=mantissa[i];
        reversindex++;
    }
    for (int j = intbitcount; j < intbitcount+floatbitcount; j++)
    {
        reversemantissa[j]=mantissa[j];
    }


    char realMantissa[mantissaBits];
    for (int i = 0; i < mantissaBits; i++)
    {
        realMantissa[i]=reversemantissa[i+1];
    }
    
    int n=mantissaBits;
    float sum=0;
    for (int i=n; i <= intbitcount+floatbitcount; i++)
    {
        if (reversemantissa[i+2]=='1')
        {
            sum+=1.0/power(2,i-n+1);
        }

    }
    if (sum>0.5)
    {
        realMantissa[mantissaBits-1]='1';
    }
    else if (sum <0.5)
    {
        realMantissa[mantissaBits-1]='0';
    }
    else if(realMantissa[mantissaBits-1]=='1'){
        int carry=1;
        sum=0;
        for (int i = mantissaBits; i >=0; i--)
        {
            sum=realMantissa[i]-'0'+carry;
            if (sum==2)
            {
                realMantissa[i]='0';
                carry=1;
            }
            else
                carry=0;
        }
    }
    
    //REAL EXPONENT
    char reverseExponent[exponentBits];
    int reversindex2=0;
    for (int i = exponentBits-1; i >= 0; i--)
    {
        reverseExponent[reversindex2]=exponent[i];
        reversindex2++;
    }

    //FULL BINARY
    binary[0]=signbit;
    for (int i = 1; i <= exponentBits; i++)
    {
        binary[i]=reverseExponent[i-1];
    }
    
    for (int i = exponentBits+1; i < totalBinaryBits; i++)
    {
        binary[i]=realMantissa[i-(exponentBits+1)];
    }

    // for (size_t i = 0; i < totalBinaryBits; i++)
    // {
    //     printf("%c",binary[i]);
    // }
    // printf("\n");
    
    //binary to hex
    char hex[2*byteSize];
    int sum2 = 0;
    int ind2 = 0;

    char revbinary[totalBinaryBits];
    int ind = 0;
    for(int i = totalBinaryBits-1; i>=0; i--){
        revbinary[ind] = binary[i];
        ind++;
    }

    ind2=0;

    for(int i = 0; i<totalBinaryBits; i++){

        if(revbinary[i] == '1'){
            sum2 = sum2 + power(2, i%4);
        }

        if( (i % 4 == 3) || i == 15){
            switch (sum2) {
                case 0:
                    hex[ind2] = '0';
                    break;
                case 1:
                    hex[ind2] = '1';
                    break;
                case 2:
                    hex[ind2] = '2';
                    break;
                case 3:
                    hex[ind2] = '3';
                    break;
                case 4:
                    hex[ind2] = '4';
                    break;
                case 5:
                    hex[ind2] = '5';
                    break;
                case 6:
                    hex[ind2] = '6';
                    break;
                case 7:
                    hex[ind2] = '7';
                    break;
                case 8:
                    hex[ind2] = '8';
                    break;
                case 9:
                    hex[ind2] = '9';
                    break;
                case 10:
                    hex[ind2] = 'A';
                    break;
                case 11:
                    hex[ind2] = 'B';
                    break;
                case 12:
                    hex[ind2] = 'C';
                    break;
                case 13:
                    hex[ind2] = 'D';
                    break;
                case 14:
                    hex[ind2] = 'E';
                    break;
                case 15:
                    hex[ind2] = 'F';
                    break;
                default:
                printf("something wrong\n");
                    break;
            }
            ind2++;
            sum2 = 0;
        }
    }

    char *endian = (char*)malloc(sizeof(char)*(3*byteSize));

    int hexIndex;

    if(orderType == littleEndian)
    {
    
        /*
            9E14
            little = E941
            41E9
        */

        hexIndex=0;
        
        for (size_t i = 0; i < 3*byteSize-1; i++)
        {
            if(i%3==0)
                endian[i] = hex[hexIndex+1];
            else if(i%3==1)
                endian[i] = hex[hexIndex];
            else
            {
                endian[i] = ' ';
                hexIndex+=2;
            }
        }
    }
    else
    {
        hexIndex = 2*byteSize-1;
        for (size_t i = 0; i <3*byteSize-1; i++)
        {
            if(i%3==0)
            {
                endian[i] = hex[hexIndex];
            }
            else if(i%3==1)
            {   
                endian[i] = hex[hexIndex-1];
            }
            else
            {
                endian[i] = ' ';
                hexIndex-=2;
            }
        }
    }

    endian[3*byteSize-1] = '\0';
    return endian;        
}