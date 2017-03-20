//
// Created by Sol Jennings on 13/3/17.
//
// Includes common functions used in both hiding and unhiding
#include <stdlib.h>
#include "common.h"

// Gets the type of image based on the magic number read from the file header
enum ImageType getImageType(FILE *file_ptr) {
    int firstChar, secondChar;
    rewind(file_ptr);

    firstChar = getc(file_ptr);
    secondChar = getc(file_ptr);

    if (firstChar == 'P' && secondChar == '6') {
        return ppm;
    }

    if (firstChar == 'B' && secondChar == 'M') {
        return bmp;
    }

    return unsupported;
}

// Prints an error message and exits. Also puts the error message in stderr
// Also closes a file if it is open
void errorAndExit(char *error, FILE *file_ptr) {
    if (file_ptr != NULL) {
        fclose(file_ptr);
    }
    fprintf(stderr, "\nError: %s\n", error);
    exit(1);
}

// Prints a message and exits
// Also closes a file if it is open
void messageAndExit(char *message, FILE *file_ptr) {
    if (file_ptr != NULL) {
        fclose(file_ptr);
    }
    fprintf(stdout, "\n%s\n", message);
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
