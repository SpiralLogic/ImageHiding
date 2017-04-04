/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains the functions for decoding a message in a BMP
*/

#include "bmpUnhide.h"
#include "bmpCommon.h"
#include "commonUnhide.h"

/**
 * Unhides an encoded message from a BMP file
*/
void unhideBmp(FILE *file_ptr) {
    struct ImageInfo imageInfo;

    imageInfo = getBmpImageInfo(file_ptr);

    if (!imageInfo.successRead) {
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }

#ifdef DEBUG
    printImageInfo(&imageInfo);
#endif

    if (imageInfo.depth != BMP_IMAGE_BITS) {
        errorAndExit("Must be a 24bit image", file_ptr);
    }

    decodeImage(file_ptr, &imageInfo);

    messageAndExit("\n\nFinished decoding!", file_ptr);
}
