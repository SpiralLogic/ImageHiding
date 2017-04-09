/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains all the common functionality to unhide an image
*/
#include <stdio.h>
#include <stdlib.h>

#include "commonUnhide.h"
#include "bmpCommon.h"
#include "ppmCommon.h"
/**
 * decodes a 24 bit image from a  file. A null terminator \0 marks the end of the encoded message
*/
void decodeImage(char* inputFile) {
    int messageChar = 0;
    int nextByte;
    int currentBit = 0;
    struct ImageInfo *imageInfo_ptr;
    struct ImageInfo imageInfo;
    enum ImageType imageType;
    FILE *inputfile_ptr;

    inputfile_ptr = fopen(inputFile, "r");

    if (inputfile_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    // Work out input image information
    imageType = getImageType(inputfile_ptr);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", inputfile_ptr);
    }

    if (imageType == ppm) {
        imageInfo = verifyAndGetPpmInfo(inputfile_ptr);
    } else if (imageType == bmp) {
        imageInfo = verifyAndGetBmpInfo(inputfile_ptr);
    }

    imageInfo_ptr = &imageInfo;
    imageInfo_ptr->filename = inputFile;

    // decode message in pixel map
    fseek(inputfile_ptr, imageInfo_ptr->pixelMapOffset, SEEK_SET);

    while ((nextByte = fgetc(inputfile_ptr)) != EOF)
    {
        // Left shift message character and decode the next bit
        messageChar <<= 1;
        messageChar |= nextByte & 0x01;
        if (currentBit == 7) {
            if (messageChar == '\0') {
                break;
            }
            printf("%c", messageChar);
            currentBit = 0;
            messageChar = 0;
        } else {
            currentBit++;
        }
    }

    fclose(inputfile_ptr);
}
