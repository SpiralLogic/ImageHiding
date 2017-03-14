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

void hideInPpm(FILE *file, char *message) {
    struct ImageInfo imageInfo = getPpmImageInfo(file);

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image depth not supportec");
    }

    if (!doesMessageFit(imageInfo, message)) {
        errorAndExit("Message does not fit image");
    }

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    encodeImage(file, imageInfo, PPM_OUTPUT_FILE, message);

    fclose(file);
}
