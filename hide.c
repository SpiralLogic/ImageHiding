/*
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for hiding a message in an image file
*/

#include <stdlib.h>
#include <string.h>

#include "ppmHide.h"
#include "bmpHide.h"
#include "common.h"
#include "commonHide.h"
#include "hide.h"

/*
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct encode function to encode the message into the image file.
*/
int main(int argc, char *argv[]) {
    char *imageFile;
    char *outputFile;
    enum ImageType imageType;
    struct ImageInfo imageInfo;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageFile = argv[1];
    outputFile = argv[2];

    FILE *file_ptr = fopen(imageFile, "r");

    if (file_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    imageType = getImageType(file_ptr);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", file_ptr);
    }

    if (imageType == ppm) {
        imageInfo = verifyAndGetPpmInfo(file_ptr);
    } else if (imageType == bmp) {
        imageInfo = verifyAndGetBmpInfo(file_ptr);
    }

    readAndEncodeMessage(file_ptr, &imageInfo, outputFile);
    fclose(file_ptr);
    printf("\nSuccessfully hid message in %s!\n", outputFile);

    return 0;
}

/*
 * displays the use for this command
*/
void usage() {
    printf("\nUsage\n");
    printf("./hide inputimage outputfile\n");
}