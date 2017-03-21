//
// Created by Sol Jennings on 13/3/17.
//
// Main executable for unhiding a message in an image file
#include "common.h"
#include "ppmUnhide.h"
#include "bmpUnhide.h"

void usage();

// Parses input arguments to make sure they are valid, determines the input file and then uses the
// correct decode function to decode the message from the image file.
int main(int argc, char *argv[]) {
    char *imageFile;
    enum ImageType imageType;

    if (argc != 2) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageFile = argv[1];

    FILE *file_ptr = fopen(imageFile, "r");

    if (file_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    imageType = getImageType(file_ptr);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", file_ptr);
    }

    if (imageType == ppm) {
        unhidePpm(file_ptr);
    } else if (imageType == bmp) {
        unhideBmp(file_ptr);
    }
    
    return 0;
}

// displays the use for this command
void usage() {
    printf("\nUsage\n");
    printf("./unhide filename\n");
}