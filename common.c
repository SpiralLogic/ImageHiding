//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"

enum ImageType getImageType(FILE *file) {
    enum ImageType imageType = unsupported;

    rewind(file);

    if (getc(file) == 'P' && getc(file) == '6') {
        imageType = ppm;
    }

    return imageType;
}

void printImageInfo(struct ImageInfo *imageSize) {
    printf("width %d\n", (*imageSize).width);
    printf("height %d\n", (*imageSize).height);
    printf("depth %d\n", (*imageSize).depth);
    printf("header lines %ld\n", (*imageSize).imageMapPosition);
}

void printByteBits(int byte) {
    for (int j = 0; j < 8; j++) {
        printf("%d",(byte << j & 0x80)/ 0x80);
    }
    printf("\n");
}

void errorAndExit(char error[]) {
    printf("Error: %s\n", error);
    exit(1);
}