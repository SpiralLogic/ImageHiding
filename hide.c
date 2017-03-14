//
// Created by Sol Jennings on 13/3/17.
//
// Main executable for hiding a message in an image file
#include "ppmHide.h"
#include "bmpHide.h"
#include "common.h"

// Parses input arguments to make sure they are valid, determines the input file and then uses the
// correct encode function to encode the message into the image file.
int main(int argc, char *argv[]) {
    char *secretMessage;
    char *imageFile;
    enum ImageType imageType;

    if (argc < 3) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];
    secretMessage = argv[2];

    FILE *file = fopen(imageFile, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    imageType = getImageType(file);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported");
    }
    if (imageType == ppm) {
        hideInPpm(file, secretMessage);
        messageAndExit("Successfully hid message in PPM file");

    } else if (imageType == bmp) {
        hideInBmp(file, secretMessage);
        messageAndExit("Successfully hid message in BMP file");
    }

    return 0;
}
