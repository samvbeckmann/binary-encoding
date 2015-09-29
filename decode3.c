#include <stdio.h>
#include "decode.h"

extern char getBits();

void decode3()
{
    char fileName[30];
    printf("Enter the file to be decoded: ");
    scanf("%s", fileName);
    FILE *fp = fopen(fileName, "rb");

    unsigned char header[34];
    fread(header, 1, 32, fp);
    if ((header[0] != 90) | (header[1] != 90))
    {
        // TODO ERROR
    }

    printf("Name 1: %.*s\n", 10, header + 4);
    printf("Name 2: %.*s\n", 10, header + 14);
    printf("Group: %c\n", header[24]);
    printf("Class: %.*s\n", 7, header + 25);
    printf("Num Bdays: %u\n", header[33]);

    int size = (int) (3*header[33]) + 1;

    unsigned char bdays[size];
    fread(bdays, 1, (unsigned) size, fp);
    int i;
    for(i = 0; i < header[33]; i++)
    {
        unsigned char id = getBits(8, bdays);
        unsigned char bMonth = getBits(8, bdays);
        unsigned char day = getBits(5, bdays);
        int year = 1994 + getBits(3, bdays);
        if (day)
        {
            printf("***************\n");
            printf("ID: %u\n", id);
            printf("Month: %u\n", bMonth);
            printf("Day: %u\n", day);
            printf("Year: %d\n", year);
        }
    }
}
