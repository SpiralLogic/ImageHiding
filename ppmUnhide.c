//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"
#include "ppmCommon.h"
#include "ppmUnhide.h"

#define PPM_COLOR_DEPTH 255

void unhidePpm(FILE *file) {
    struct ImageInfo imageInfo;

    imageInfo = getImageInfo(file);

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }

    printf("width %d\n", imageInfo.width);
    printf("height %d\n", imageInfo.height);
    printf("depth %d\n", imageInfo.depth);
    printf("image map position: %ld\n", imageInfo.imageMapPosition);

    decodeImage(file, imageInfo);

    fclose(file);
}

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
