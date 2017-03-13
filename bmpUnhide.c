//
// Created by Sol Jennings on 13/3/17.
//

#include "bmpUnhide.h"
#include "common.h"
#include "bmpCommon.h"
#include "commonUnhide.h"

#define BMP_COLOR_DEPTH 24


void unhideBmp(FILE *file) {
    struct ImageInfo imageInfo;

    imageInfo = getBmpImageInfo(file);

    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Must be a 24bit image");
    }

    printImageInfo(&imageInfo);

    decodeImage(file, imageInfo);

    fclose(file);
}
