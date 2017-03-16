//
// Created by Sol Jennings on 13/3/17.
//
// Contains the common functionality required for PPM file
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "ppmCommon.h"

// Reads the information about a PPM image from the header
struct ImageInfo getPpmImageInfo(FILE *file_ptr) {
    struct ImageInfo imageInfo = {.height = 0, .width =0, .depth = 0, .pixelMapOffset = 0};
    bool headerComplete = false;
    int nextChar;
    int currentDimension = 0;
    int dimensionValue;

    // Skip the magic number
    fseek(file_ptr, 2, SEEK_SET);

    while (!headerComplete) {
        // Get the next character
        nextChar = getc(file_ptr);

        if (nextChar == EOF) {
            errorAndExit("Could not read a complete header", file_ptr);
        }

        // Pesky comments can be skipped
        if (nextChar == '#') {
            moveFileToNextLine(file_ptr);
            continue;
        }

        // skip any whitespace
        if (nextChar == ' ' || nextChar == '\t' || nextChar == '\n' || nextChar == '\r') {
            continue;
        }

        // put character back on so that we can fscan it
        ungetc(nextChar, file_ptr);
        dimensionValue = scanDimension(file_ptr);

        // No dimension value found ! remove the character again keep searching
        if (dimensionValue < 0) {
            // we didn't scan a dimension that means this character is garbage.
            errorAndExit("Malformed header", file_ptr);
            continue;
        }

        switch (currentDimension) {
            case 0:
                imageInfo.width = dimensionValue;
                currentDimension++;
                break;
            case 1:
                imageInfo.height = dimensionValue;
                currentDimension++;
                break;
            case 2:
                imageInfo.depth = dimensionValue;
                moveFileToNextLine(file_ptr);
                headerComplete = true;
                break;
            default:
                errorAndExit("Bad header detected", file_ptr);
        }
    }

    // Store the start of the image pixel map
    imageInfo.pixelMapOffset = ftell(file_ptr) + 1;

    return imageInfo;
}

// Scans a dimension from the image file and return -1 if none was found
int scanDimension(FILE *file_ptr) {
    int dimension;
    if (fscanf(file_ptr, "%i", &dimension) < 1) {
        return -1;
    }

    return dimension;
}

// Moves to the next line of the file
void moveFileToNextLine(FILE *file_ptr) {
    int nextChar;
    while ((nextChar = getc(file_ptr)) != EOF) {
        if (nextChar == '\n') {
            return;
        }
    };

    errorAndExit("End of file_ptr reached before next line", file_ptr);
}
