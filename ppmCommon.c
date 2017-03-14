//
// Created by Sol Jennings on 13/3/17.
//
// Contains the common functionality required for PPM file
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "ppmCommon.h"

// Reads the information about a PPM image from the header
struct ImageInfo getPpmImageInfo(FILE *file) {
    struct ImageInfo imageInfo = {.height = 0, .width =0, .depth = 0, .pixelMapOffset = 0};
    bool headerComplete = false;
    int nextChar;
    int currentDimension = 0;
    int dimensionValue;

    // Skip the magic number
    fseek(file, 2, SEEK_SET);

    while (!headerComplete) {
        // Get the next character and then put it back on so that we can fscan it later
        nextChar = getc(file);
        ungetc(nextChar, file);

        // Pesky comments can be skipped
        if (nextChar == '#' || nextChar == '\n') {
            moveFileToNextLine(file);
            continue;
        }

        dimensionValue = scanDimension(file);

        // No dimension value found ! remove the character again keep searching
        if (dimensionValue < 0) {
            getc(file);
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
                headerComplete = true;
                break;
            default:
                errorAndExit("Bad header detected");
        }
    }

    // Store the start of the image pixel map
    imageInfo.pixelMapOffset = ftell(file) + 1;

    return imageInfo;
}

// Scans a dimension from the image file and return -1 if none was found
int scanDimension(FILE *file) {
    int dimension;

    if (fscanf(file, "%d", &dimension) < 1) {
        return -1;
    }

    return dimension;
}

// Moves to the next line of the file
void moveFileToNextLine(FILE *file) {
    int nextChar;
    while ((nextChar = getc(file)) != EOF) {
        if (nextChar == '\n') {
            return;
        }
    };

    errorAndExit("End of file reached before next line");
}
