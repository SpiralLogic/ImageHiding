#include "ppmHide.h"
#include "bmpHide.h"
#include "common.h"

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

    } else if (imageType == bmp) {
        hideInBmp(file, secretMessage);
    }

    return 0;
}
