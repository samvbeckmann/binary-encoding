#include <stdio.h>

unsigned char getBits(unsigned char bits, unsigned char* *data)
{
    static char currentValue;
    static char position;
    unsigned char result;

    if (bits + position <= 8)
    {
        result = (*data[currentValue] >> ((unsigned char) 8 - position - bits)) &
                (((unsigned char) 1 << bits) - (unsigned char) 1);
        if (position + bits == 8)
        {
            position = 0;
            currentValue++;
        }
    } else
    {
        unsigned char part1 = (*data[currentValue] << (bits + position - (unsigned char) 8)) &
                (((unsigned char) 1 << bits) - (unsigned char) 1);
        currentValue++;
        unsigned char part2 = *data[currentValue] >> (16 - bits - position);
        result = part1 | part2;

        position = (position + bits) % (unsigned char) 8;
    }

    return result;
}

int main()
{
    char fileName[30];
    printf("Enter the file to be decoded:");
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
    printf("Group: %u\n", header + 22);
    printf("Class: %.*s\n", 7, header + 23);
    printf("Num Bdays: %u", header + 30);

    int size = (int) 2.125*header[31] + 1;
    unsigned char month = 0;
    unsigned char bdays[size];
    for(int i = 0; i < header[31]; i++)
    {
        unsigned char id = getBits(8, *bdays);
        month += getBits(2, *bdays);
        unsigned char bMonth = month;
        unsigned char day = getBits(5, *bdays);
        int year = 1995 + getBits(2, *bdays);
        if (day)
        {
            printf("***************");
            printf("ID: %u\n", id);
            printf("Month: %u\n", bMonth);
            printf("Day: %c\n", day);
            printf("Year: %d", year);
        }
    }

    return 0;
}
