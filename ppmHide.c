//
// Created by Sol Jennings on 13/3/17.
//

#include <memory.h>
#include "common.h"
#include "ppmCommon.h"
#include "ppmHide.h"

#define PPM_COLOR_DEPTH 255

void hideInPpm(FILE *file, char *message) {

    struct ImageInfo imageSize;

    imageSize = getImageInfo(file);

    if (imageSize.depth != PPM_COLOR_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }

    if (!doesMessageFit(imageSize, message)) {
        errorAndExit("Message does not fit image");
    }

    printf("width %d\n", imageSize.width);
    printf("height %d\n", imageSize.height);
    printf("depth %d\n", imageSize.depth);
    printf("header lines %ld\n", imageSize.imageMapPosition);

    encodeImage(file, imageSize, message);

    fclose(file);
}

void encodeImage(FILE *file, struct ImageInfo imageInfo, char *message) {
    FILE *outfile = fopen("outfile.ppm", "w+");

    if (outfile == NULL) {
        errorAndExit("Cannot open output file");
    }

    copyHeader(file, outfile, imageInfo);

    int messageLength = (int) strlen(message) + 1;
    int messageBit;
    int nextByte;
    for (int i=0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {
            messageBit = (message[i] << j & 0x80)/0x80;
            nextByte = getc(file);
            if (nextByte == EOF) {
                fclose(outfile);
                remove("outfile.ppm");
                errorAndExit("Cannot encode into an incomplete image");
            }
            nextByte = (nextByte & 0xFE) | messageBit;
            putc(nextByte, outfile);
        }
    }

    while ((nextByte = fgetc(file)) != EOF) {
        fputc(nextByte, outfile);
    }
    fclose(outfile);
}

void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file);

    while ((nextByte = fgetc(file))!=EOF && charsCopied < imageInfo.imageMapPosition)
    {
        fputc(nextByte, outfile);
        charsCopied++;
    }
    if (nextByte == EOF) {
        errorAndExit("Unexpected end of file");
    }
}

bool doesMessageFit(struct ImageInfo info, char *message) {

    if (strlen(message) > sizeof(int) * 8) {
        return false;
    }

    int length = (int) strlen(message) + 1;

    return (length * 8) < (info.height * info.width * 3);
}
