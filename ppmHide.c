/*
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains all of the hide for ppm functionality
*/
#include <memory.h>

#include "common.h"
#include "commonHide.h"
#include "ppmCommon.h"
#include "ppmHide.h"

/*
 * Get's the image information for a PPM image and verifies that
 * A message can be hidden in it
 */
struct ImageInfo verifyAndGetPpmInfo(FILE *file_ptr) {
    struct ImageInfo imageInfo = getPpmImageInfo(file_ptr);

    if (!imageInfo.successRead) {
        errorAndExit(imageInfo.errorMesssage, file_ptr);
    }

#ifdef DEBUG
    printImageInfo(&imageInfo);
#endif

    if (imageInfo.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image depth not supported", file_ptr);
    }

    return imageInfo;
}
