//
// Created by Sol Jennings on 13/3/17.
//

// Contains the functions for hiding a message in a BMP

#include "common.h"
#include "commonHide.h"
#include "bmpCommon.h"
#include "bmpHide.h"

// Hides the given message in a bmp file_ptr
// only 24 bit BMPs are support as these are the most popular and follow the same
// pixel map structure as a PPM
void hideInBmp(FILE *file_ptr, char *outputFile, char *message){
    struct ImageInfo imageInfo = getBmpImageInfo(file_ptr);

    if (!imageInfo.successRead) {
        freeSecretMessage();
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }

#ifdef DEBUG
    printImageInfo(&imageInfo);
#endif

    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        freeSecretMessage();
        errorAndExit("Image must be 24 bit", file_ptr);
    }

    if (!doesMessageFit(&imageInfo, message)) {
        freeSecretMessage();
        errorAndExit("Message does not fit image", file_ptr);
    }

    encodeImage(file_ptr, &imageInfo, outputFile, message);
};

