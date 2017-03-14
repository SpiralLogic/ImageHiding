//
// Created by Sol Jennings on 13/3/17.
//
// Contains the functions for decoding a message in a BMP
#include "bmpUnhide.h"
#include "common.h"
#include "bmpCommon.h"
#include "commonUnhide.h"

#define BMP_COLOR_DEPTH 24

// Unhides an encoded message from a BMP file
void unhideBmp(FILE *file) {
    struct ImageInfo imageInfo;

    imageInfo = getBmpImageInfo(file);

    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Must be a 24bit image");
    }

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    decodeImage(file, imageInfo);

    fclose(file);
}
