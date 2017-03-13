//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"
#include "commonHide.h"
#include "bmpCommon.h"
#include "bmpHide.h"

#define BMP_COLOR_DEPTH 24

void hideInBmp(FILE *file, char *message){
    struct ImageInfo imageInfo = getBmpImageInfo(file);

    printImageInfo(&imageInfo);


    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Image must be 24 bit");
    }

    if (!doesMessageFit(imageInfo, message)) {
        errorAndExit("Message does not fit image");
    }

    encodeImage(file, imageInfo, "output.bmp", message);

    fclose(file);
};

