//
// Created by Sol Jennings on 13/3/17.
//

// Contains all of the hide for ppm functionality
#include <memory.h>

#include "common.h"
#include "commonHide.h"
#include "ppmCommon.h"
#include "ppmHide.h"

#define PPM_COLOR_DEPTH 255

void hideInPpm(FILE *file_ptr, char *outputFile, char *message) {
    struct ImageInfo imageInfo = getPpmImageInfo(file_ptr);

    if (imageInfo.successRead == false) {
        freeSecretMessage();
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }

#ifdef DEBUG
    printImageInfo(&imageInfo);
#endif

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        freeSecretMessage();
        errorAndExit("Image depth not supported", file_ptr);
    }

    if (!doesMessageFit(&imageInfo, message)) {
        freeSecretMessage();
        errorAndExit("Message does not fit image", file_ptr);
    }

    encodeImage(file_ptr, &imageInfo, outputFile, message);
}
