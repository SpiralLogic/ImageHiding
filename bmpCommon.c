/*
 * Created by Sol Jennings on 13/3/17.
 *
 * All of the common BMP functions.
 *
*/
#include "common.h"
#include "bmpCommon.h"

/*
 * Determines the image information of BMP file
*/
struct ImageInfo getBmpImageInfo(FILE *file_ptr) {
    struct ImageInfo imageInfo = {.height = 0, .width =0, .depth = 0, .pixelMapOffset = 0, .successRead = false};

    // Get the furthest piece of information first so that we can test to make sure
    // all of the header is going to be there
    fseek(file_ptr, 28, SEEK_SET);
    fread(&imageInfo.depth, 2, 1, file_ptr);

    if (feof(file_ptr) != 0 || ferror(file_ptr) != 0) {
        imageInfo.successRead = true;
        imageInfo.errorMesssage = "Malformed BMP Header";
        return imageInfo;
    }

    // Find where the pixel information starts
    fseek(file_ptr, 10, SEEK_SET);
    fread(&imageInfo.pixelMapOffset, 4, 1, file_ptr);

    // find the width
    fseek(file_ptr, 18, SEEK_SET);
    fread(&imageInfo.width, 4, 1, file_ptr);

    // find the height
    fseek(file_ptr, 22, SEEK_SET);
    fread(&imageInfo.height, 4, 1, file_ptr);

    imageInfo.successRead = true;

    return imageInfo;
}