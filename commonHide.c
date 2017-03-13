//
// Created by Sol Jennings on 13/3/17.
//

#include <memory.h>
#include "commonHide.h"
#include "common.h"

void encodeImage(FILE *file, struct ImageInfo imageInfo, char *outputFile, char *message) {
    FILE *outfile = fopen(outputFile, "w+");

    if (outfile == NULL) {
        errorAndExit("Cannot open output file");
    }

    copyHeader(file, outfile, imageInfo);

    fseek(file, imageInfo.imageMapPosition, SEEK_SET);

    int messageLength = (int) strlen(message) + 1;
    int messageBit;
    int nextByte;

    for (int i=0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {
            messageBit = (message[i] << j & 0x80)/0x80;
            nextByte = getc(file);
            if (nextByte == EOF) {
                fclose(outfile);
                remove(outputFile);
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


bool doesMessageFit(struct ImageInfo info, char *message) {

    if (strlen(message) > sizeof(int) * 8) {
        return false;
    }

    int length = (int) strlen(message) + 1;

    return (length * 8) < (info.height * info.width * 3);
}


void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file);

    while ((nextByte = fgetc(file)) != EOF && charsCopied < imageInfo.imageMapPosition)
    {
        fputc(nextByte, outfile);
        charsCopied++;
    }

    if (nextByte == EOF) {
        errorAndExit("Unexpected end of file");
    }
}
