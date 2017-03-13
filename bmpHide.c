//
// Created by Sol Jennings on 13/3/17.
//

#include <memory.h>
#include "common.h"
#include "bmpCommon.h"
#include "bmpHide.h"

#define BMP_COLOR_DEPTH 24

void hideInBmp(FILE *file, char *message){
    struct ImageInfo imageInfo = getBmpImageInfo(file);

    printImageInfo(&imageInfo);

    
    if (imageInfo.depth != BMP_COLOR_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }
/*

    if (!doesMessageFit(imageInfo, message)) {
        errorAndExit("Message does not fit image");
    }
*/

/*

    encodeBmpImage(file, imageInfo, message);
*/

    fclose(file);
};
