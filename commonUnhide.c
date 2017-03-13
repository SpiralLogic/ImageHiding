//
// Created by Sol Jennings on 13/3/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "commonUnhide.h"


void decodeImage(FILE *file, struct ImageInfo imageInfo) {
    int messageChar = 0;
    int nextByte;
    int currentBit = 0;

    fseek(file, imageInfo.imageMapPosition, SEEK_SET);

    while ((nextByte = fgetc(file)) != EOF)
    {
        messageChar <<= 1;
        messageChar |= nextByte & 0x01;
        if (currentBit == 7) {
            if (messageChar == '\0') {
                printf("\nFinished!");
                exit(0);
            }
            printf("%c", messageChar);
            currentBit = 0;
            messageChar = 0;
        } else {
            currentBit++;
        }
    }
}
