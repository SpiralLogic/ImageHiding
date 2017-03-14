//
// Created by Sol Jennings on 13/3/17.
//
// Contains the functions for hiding a message in a BMP
#include "common.h"
#include "commonHide.h"
#include "bmpCommon.h"
#include "bmpHide.h"

#define BMP_OUTPUT_FILE "output.bmp"
#define BMP_COLOR_DEPTH 24

// Hides the given message in a bmp file
// only 24 bit BMPs are support as these are the most popular and follow the same
// pixel map structure as a PPM
void hideInBmp(FILE *file, char *message){
    struct ImageInfo imageInfo = getBmpImageInfo(file);

    #ifdef DEBUG
    printImageInfo(&imageInfo);
    #endif

    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Image must be 24 bit");
    }

    if (!doesMessageFit(imageInfo, message)) {
        errorAndExit("Message does not fit image");
    }

    encodeImage(file, imageInfo, BMP_OUTPUT_FILE, message);

    fclose(file);
};

