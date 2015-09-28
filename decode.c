#include <stdio.h>
#include "decode.h"

unsigned char getBits(unsigned char bits, unsigned char data[])
{
    static char currentValue;
    static char position;
    unsigned char result;

    if (bits + position <= 8)
    {
        result = (data[currentValue] >> ((unsigned char) 8 - position - bits)) &
                (((unsigned char) 1 << bits) - (unsigned char) 1);
        position += bits;
        if (position >= 8)
        {
            position = 0;
            currentValue++;
        }
    } else
    {
        unsigned char part1 = (data[currentValue] << (bits + position - (unsigned char) 8)) &
                (((unsigned char) 1 << bits) - (unsigned char) 1);
        currentValue++;
        unsigned char part2 = data[currentValue] >> (16 - bits - position);
        result = part1 | part2;

        position = (position + bits) % (unsigned char) 8;
    }

    return result;
}

void decode()
{
    char fileName[30];
    printf("Enter the file to be decoded: ");
    scanf("%s", fileName);
    FILE *fp = fopen(fileName, "rb");

    unsigned char header[32];
    fread(header, 1, 32, fp);
    if ((header[0] != 90) | (header[1] != 90))
    {
        // TODO ERROR
    }

    printf("Name 1: %.*s\n", 10, header + 2);
    printf("Name 2: %.*s\n", 10, header + 12);
    printf("Group: %u\n", header[22]);
    printf("Class: %.*s\n", 7, header + 23);
    printf("Num Bdays: %u\n", header[31]);

    int size = (int) (2.125*header[31]) + 1;
    unsigned char month = 1;
    unsigned char bdays[size];
    fread(bdays, 1, (unsigned) size, fp);
    int i;
    for(i = 0; i < header[31]; i++)
    {
        unsigned char id = getBits(8, bdays);
        month += getBits(2, bdays);
        unsigned char bMonth = month;
        unsigned char day = getBits(5, bdays);
        int year = 1994 + getBits(2, bdays);
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
