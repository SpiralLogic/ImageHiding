#include <stdio.h>
#include "ppmUnhide.h"
#include "common.h"

int main(int argc, char *argv[]) {
    char *imageFile;

    if (argc < 2) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];

    FILE *file = fopen(imageFile, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    if (getImageType(file) == unsupported) {
        errorAndExit("Image type unsupported");
    }

    unhidePpm(file);

    return 0;
}
