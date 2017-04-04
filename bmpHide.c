/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains the functions for hiding a message in a BMP
*/

#include "common.h"
#include "commonHide.h"
#include "bmpCommon.h"
#include "bmpHide.h"

/**
 * Hides the given message in a bmp file
 * only 24 bit BMPs are support as these are the most popular and use 255 bits for each pixel
*/
struct ImageInfo verifyAndGetBmpInfo(FILE *file_ptr) {
    struct ImageInfo imageInfo = getBmpImageInfo(file_ptr);

    if (!imageInfo.successRead) {
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }

#ifdef DEBUG
    printImageInfo(&imageInfo);
#endif

    if (imageInfo.depth != BMP_IMAGE_BITS) {
        errorAndExit("Image must be 24 bit", file_ptr);
    }

    return imageInfo;
};

