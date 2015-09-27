#include <stdio.h>
#include <math.h>

int bit2byte(char bit, FILE *file) {
    static char output;
    static char index;

    index --;
    output = output | bit << index;

//    if (bit) {
//        output = (output | (char) pow(2, 15 - index));
//    }

    if (index == 0) {
        fputc(output, file);
        index = 8;
        output = 0;
        return 1;
    } else
        return 0;
}

int main() {

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

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fputc(names[i][j], file);
        }
    }

    fputc(2, file);

    char className[8] = {"ECE2263"};
    for (int i = 0; i < 7; i++)
    {
        fputc(className[i], file);
    }

    fputc(0, file);
    fputc(17, file);

    /* End of Header */

    unsigned char month = 0;

    for (int i = 0; i < 17; i++)
    {
        /* Write id */
        fputc(class[i][0], file);

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
        unsigned char yearOffset = (unsigned char) 94 - class[i][3];
        switch (yearOffset)
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
                //TODO ERROR
                break;
        }
    }

    while (!bit2byte(0,file));

    // TODO close file.

        return 0;
}