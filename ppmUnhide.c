//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"
#include "commonUnhide.h"
#include "ppmCommon.h"
#include "ppmUnhide.h"

#define PPM_COLOR_DEPTH 255

void unhidePpm(FILE *file) {
    struct ImageInfo imageInfo;

    imageInfo = getPpmImageInfo(file);

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }

    printImageInfo(&imageInfo);

    decodeImage(file, imageInfo);

    fclose(file);
}
