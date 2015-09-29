#include <stdio.h>
#include "decode.h"
#include "encode.h"

extern void encode();
extern void decode();
extern void decode3();

void main()
{
    printf("Press 'e' to encode, 't' to decode using method 3, any other key to decode default method: ");
    char result;
    scanf("%c", &result);
    if (result == 'e')
    {
        encode();
    } else if (result == 't'){
    	decode3();
    } else
        decode();
}
