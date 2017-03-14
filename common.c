//
// Created by Sol Jennings on 13/3/17.
//
// Includes common functions used in both hiding and unhiding
#include <stdlib.h>
#include "common.h"

// Gets the type of image based on the magic number read from the file header
enum ImageType getImageType(FILE *file) {
    int firstChar, secondChar;
    rewind(file);

    firstChar = getc(file);
    secondChar = getc(file);

    if (firstChar == 'P' && secondChar == '6') {
        return ppm;
    }

    if (firstChar == 'B' && secondChar == 'M') {
        return bmp;
    }

    return unsupported;
}

// Prints an error message and exits. Also puts the error message in stderr
void errorAndExit(char error[]) {
    fprintf(stderr, "Error: %s\n", error);
    exit(1);
}

// Prints a message and exits
void messageAndExit(char message[]) {
    fprintf(stdout, "%s\n", message);
    exit(0);
}

#ifdef DEBUG

// Prints the information about an image
void printImageInfo(struct ImageInfo *imageInfo) {
    printf("width %d\n", (*imageInfo).width);
    printf("height %d\n", (*imageInfo).height);
    printf("depth %d\n", (*imageInfo).depth);
    printf("image offset %ld\n", (*imageInfo).pixelMapOffset);
}

// Prints a byte out as bits
void printByteBits(int byte) {
    for (int j = 0; j < 8; j++) {
        printf("%d",(byte << j & 0x80)/ 0x80);
    }
    printf("\n");
}

#endif
