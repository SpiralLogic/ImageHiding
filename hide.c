#include "ppmHide.h"
#include "common.h"

int main(int argc, char *argv[]) {
    char *secretMessage;
    char *imageFile;

    if (argc < 3) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];
    secretMessage = argv[2];

    FILE *file = fopen(imageFile, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    if (getImageType(file) == unsupported) {
        errorAndExit("Image type unsupported");
    }

    hideInPpm(file, secretMessage);

    return 0;
}
