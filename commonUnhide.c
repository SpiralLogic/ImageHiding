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
 * decodes a 24 bit image from a  file. A EOF marks the end of the encoded message
 *
 * @param inputFile input file to decode message from
 * @return true when complete message was decoded
*/
bool decodeImage(char* inputFile) {
    char messageChar = (char) '\0';
    int nextByte;
    int currentBit = 0;
    ImageInfo *imageInfo_ptr;
    ImageInfo imageInfo;
    enum ImageType imageType;
    FILE *inputFile_ptr;

    inputFile_ptr = fopen(inputFile, "r");

    if (inputFile_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    // Work out input image information
    imageType = getImageType(inputFile_ptr);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", inputFile_ptr);
    }

    if (imageType == ppm) {
        imageInfo = verifyAndGetPpmInfo(inputFile_ptr);
    } else if (imageType == bmp) {
        imageInfo = verifyAndGetBmpInfo(inputFile_ptr);
    }

    if (!imageInfo.successRead) {
        errorAndExit(imageInfo.errorMesssage, inputFile_ptr);
    }

    imageInfo_ptr = &imageInfo;
    imageInfo_ptr->filename = inputFile;

    // decode message in pixel map
    fseek(inputFile_ptr, imageInfo_ptr->pixelMapOffset, SEEK_SET);
    while ((nextByte = fgetc(inputFile_ptr)) != EOF)
    {
        // Left shift message character and decode the next bit
        messageChar <<= 1;
        messageChar |= nextByte & 0x01;
        if (currentBit == 7) {
            if (messageChar == EOF) {
                fclose(inputFile_ptr);
                return true;
            }
            printf("%c", messageChar);
            currentBit = 0;
            messageChar = (char) '\0';
        } else {
            currentBit++;
        }
    }

    fclose(inputFile_ptr);

    return false;
}
