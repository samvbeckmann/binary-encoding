#include <stdio.h>
#include "decode.h"
#include "encode.h"

extern void encode();
extern void decode();

void main()
{
    printf("Press 'e' to encode, any other key to decode: ");
    char result;
    scanf("%c", &result);
    if (result == 'e')
    {
        encode();
    } else
        decode();
}