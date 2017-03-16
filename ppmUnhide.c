//
// Created by Sol Jennings on 13/3/17.
//
// Contains all of the functionality required to unhide a message from a PPM image

#include "common.h"
#include "commonUnhide.h"
#include "ppmCommon.h"
#include "ppmUnhide.h"

#define PPM_COLOR_DEPTH 255

// unhides the message from a PPM file
void unhidePpm(FILE *file_ptr) {
    struct ImageInfo imageInfo;

    imageInfo = getPpmImageInfo(file_ptr);

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Unsupported image depth", file_ptr);
    }

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    decodeImage(file_ptr, &imageInfo);

    messageAndExit("\n\nFinished decoding!", file_ptr);
}
