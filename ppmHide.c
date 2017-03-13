//
// Created by Sol Jennings on 13/3/17.
//

#include <memory.h>
#include "common.h"
#include "commonHide.h"
#include "ppmCommon.h"
#include "ppmHide.h"

#define PPM_COLOR_DEPTH 255

void hideInPpm(FILE *file, char *message) {
    struct ImageInfo imageInfo = getPpmImageInfo(file);

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }

    if (!doesMessageFit(imageInfo, message)) {
        errorAndExit("Message does not fit image");
    }

    printImageInfo(&imageInfo);

    encodeImage(file, imageInfo, "output.ppm", message);

    fclose(file);
}
