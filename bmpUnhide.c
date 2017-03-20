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
void unhideBmp(FILE *file_ptr) {
    struct ImageInfo imageInfo;

    imageInfo = getBmpImageInfo(file_ptr);

    if (imageInfo.successRead == false) {
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }
    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Must be a 24bit image", file_ptr);
    }

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    decodeImage(file_ptr, &imageInfo);

    messageAndExit("\n\nFinished decoding!", file_ptr);
}
