#include "common.h"
#include "ppmUnhide.h"
#include "bmpUnhide.h"

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


    return 0;
}
