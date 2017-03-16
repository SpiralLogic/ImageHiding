//
// Created by Sol Jennings on 13/3/17.
//
// Contains all of the functionality

#include <memory.h>
#include "common.h"
#include "commonHide.h"
#include "ppmCommon.h"
#include "ppmHide.h"

#define PPM_COLOR_DEPTH 255
#define PPM_OUTPUT_FILE "output.ppm"

void hideInPpm(FILE *file_ptr, char *message) {
    struct ImageInfo imageInfo = getPpmImageInfo(file_ptr);

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image depth not supported", file_ptr);
    }

    if (!doesMessageFit(&imageInfo, message)) {
        errorAndExit("Message does not fit image", file_ptr);
    }

    encodeImage(file_ptr, &imageInfo, PPM_OUTPUT_FILE, message);
}
