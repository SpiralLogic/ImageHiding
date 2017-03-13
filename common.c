//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"

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

void printImageInfo(struct ImageInfo *imageSize) {
    printf("width %d\n", (*imageSize).width);
    printf("height %d\n", (*imageSize).height);
    printf("depth %d\n", (*imageSize).depth);
    printf("image offset %ld\n", (*imageSize).imageMapPosition);
}

void printByteBits(int byte) {
    for (int j = 0; j < 8; j++) {
        printf("%d",(byte << j & 0x80)/ 0x80);
    }
    printf("\n");
}

void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file);

    while ((nextByte = fgetc(file)) != EOF && charsCopied < imageInfo.imageMapPosition)
    {
        fputc(nextByte, outfile);
        charsCopied++;
    }
    if (nextByte == EOF) {
        errorAndExit("Unexpected end of file");
    }
}


void errorAndExit(char error[]) {
    fprintf(stderr, "Error: %s\n", error);
    exit(1);
}
