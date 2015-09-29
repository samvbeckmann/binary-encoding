#include <stdio.h>
#include "encode.h"

int bit2byte(char bit, FILE *file)
{
    static char output;
    static unsigned char index = 8;

    index--;
    output = output | (bit << index);

    if (index == 0)
    {
        fputc(output, file);
        index = 8;
        output = 0;
        return 1;
    } else
        return 0;
}

void encode() {

    unsigned char class[17][4] = {
            {20,  1,  10, 96},
            {18,  1,  13, 97},
            {1,   1,  9,  96},
            {12,  3,  18, 96},
            {42,  3,  04, 96},
            {34,  3,  21, 96},
            {5,   4,  10, 96},
            {255, 5,  9,  96},
            {16,  6,  26, 96},
            {10,  6,  16, 95},
            {0,   6,  6,  96},
            {127, 8,  20, 95},
            {23,  8,  25, 95},
            {21,  10, 25, 94},
            {14,  10, 28, 95},
            {4,   10, 2,  95},
            {24,  12, 14, 94}
    };

    char names[2][10] = {"Beckmann", "Liao"};

    FILE *file = fopen("birthdays.bin", "wb+");

    fputc(90, file);
    fputc(90, file);

    int i;
    for (i = 0; i < 2; i++)
    {
        int j;
        for (j = 0; j < 10; j++)
        {
            fputc(names[i][j], file);
        }
    }

    fputc(1, file);

    char className[8] = {"ECE2263"};
    for (i = 0; i < 7; i++)
    {
        fputc(className[i], file);
    }

    fputc(0, file);
    fputc(17, file);

    /* End of Header */

    unsigned char month = 1;
    int wroteByte = 0;

    for (i = 0; i < 17; i++)
    {
        /* Write id */
        unsigned char j;
        for (j = 7; j < 255; j--)
        {
            bit2byte(class[i][0] >> j & (unsigned char) 1, file);
        }

        /* Write month */
        unsigned char tempMonth = class[i][1] - month;
        switch (tempMonth)
        {
            case 0:
                bit2byte(0, file);
                bit2byte(0, file);
                break;
            case 1:
                bit2byte(0, file);
                bit2byte(1, file);
                break;
            case 2:
                bit2byte(1, file);
                bit2byte(0, file);
                break;
            case 3:
                bit2byte(1, file);
                bit2byte(1, file);
                break;
            default:
                //TODO Handler - increment by three, and write day as blank
                break;
        }

        month = class[i][1];

        /* Write day */
        unsigned char day = class[i][2];
        bit2byte(day / (unsigned char) 16, file);
        bit2byte(day % (unsigned char) 16 / (unsigned char) 8, file);
        bit2byte(day % (unsigned char) 8 / (unsigned char) 4, file);
        bit2byte(day % (unsigned char) 4 / (unsigned char) 2, file);
        bit2byte(day % (unsigned char) 2, file);

        /* Write year */
        unsigned char yearOffset =  class[i][3] - (unsigned char) 94;
        switch (yearOffset)
        {
            case 0:
                bit2byte(0, file);
                wroteByte = bit2byte(0, file);
                break;
            case 1:
                bit2byte(0, file);
                wroteByte = bit2byte(1, file);
                break;
            case 2:
                bit2byte(1, file);
                wroteByte = bit2byte(0, file);
                break;
            case 3:
                bit2byte(1, file);
                wroteByte = bit2byte(1, file);
                break;
            default:
                //TODO ERROR
                break;
        }
    }

    if (!wroteByte)
        while (!bit2byte(0,file));
}