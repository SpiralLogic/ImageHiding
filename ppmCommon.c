//
// Created by Sol Jennings on 13/3/17.
//

#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "ppmCommon.h"

struct ImageInfo getPpmImageInfo(FILE *file) {
    struct ImageInfo imageInfo = {.height = 0, .width =0, .depth = 0, .imageMapPosition = 0};
    bool headerComplete = false;
    int nextChar;
    int currentDimension = 0;
    int dimensionValue;

    fseek(file, 2, SEEK_SET);

    while (!headerComplete) {
        nextChar = getc(file);
        ungetc(nextChar, file);

        if (nextChar == '#' || nextChar == '\n') {
            moveFileToNextLine(file);
            continue;
        }

        dimensionValue = scanDimension(file);

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

    imageInfo.imageMapPosition = ftell(file) + 1;

    return imageInfo;
}

int scanDimension(FILE *file) {
    int dimension;

    if (fscanf(file, "%d", &dimension) <1) {
        return -1;
    }

    return dimension;
}

void moveFileToNextLine(FILE *file) {
    int nextChar;
    while ((nextChar = getc(file)) != EOF) {
        if (nextChar == '\n') {
            return;
        }
    };

    errorAndExit("End of file reached before next line");
}
