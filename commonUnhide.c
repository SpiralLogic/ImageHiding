//
// Created by Sol Jennings on 13/3/17.
//
// Contains all the common functionality to unhide an image
#include <stdio.h>
#include <stdlib.h>
#include "commonUnhide.h"

// decodes a 24 bit image from an inout file. A null terminator marks the end of the encoded message
void decodeImage(FILE *file, struct ImageInfo imageInfo) {
    int messageChar = 0;
    int nextByte;
    int currentBit = 0;

    fseek(file, imageInfo.pixelMapOffset, SEEK_SET);
    printf("Decoded message:\n");

    while ((nextByte = fgetc(file)) != EOF)
    {
        // Left shift message character and decode the next bit
        messageChar <<= 1;
        messageChar |= nextByte & 0x01;
        if (currentBit == 7) {
            if (messageChar == '\0') {
                messageAndExit("\n\nFinished decoding!");
            }
            printf("%c", messageChar);
            currentBit = 0;
            messageChar = 0;
        } else {
            currentBit++;
        }
    }
    errorAndExit("\nOh No! The end of the message was next reached!");
}
