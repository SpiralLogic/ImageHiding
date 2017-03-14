//
// Created by Sol Jennings on 13/3/17.
//
// Main executable for unhiding a message in an image file
#include "common.h"
#include "ppmUnhide.h"
#include "bmpUnhide.h"

// Parses input arguments to make sure they are valid, determines the input file and then uses the
// correct decode function to decode the message from xthe image file.
int main(int argc, char *argv[]) {
    char *imageFile;
    enum ImageType imageType;


    if (argc < 2) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];

    FILE *file = fopen(imageFile, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    imageType = getImageType(file);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported");
    }
    if (imageType == ppm) {
        unhidePpm(file);

    } else if (imageType == bmp) {
        unhideBmp(file);
    }

    messageAndExit("\nSuccessfully decoded message!");

    return 0;
}
