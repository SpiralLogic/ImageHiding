//
// Created by Sol Jennings on 13/3/17.
//
// Contains the common functionality required to hide an image

#include <memory.h>
#include "commonHide.h"
#include "common.h"

// Encodes a message into a 24 bit pixel map
// Each RGB colour in a pixel will store 1 bit of the message in it's least significant bit
void encodeImage(FILE *file_ptr, struct ImageInfo *imageInfo, char *outputFile, char *message) {
    FILE *outfile = fopen(outputFile, "w+");

    if (outfile == NULL) {
        errorAndExit("Cannot open output file_ptr", file_ptr);
    }

    copyHeader(file_ptr, outfile, imageInfo);

    fseek(file_ptr, imageInfo->pixelMapOffset, SEEK_SET);

    int messageLength = (int) strlen(message) + 1;
    int messageBit;
    int nextByte;

    // encode the message into the image and output it to the file
    for (int i=0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {
            // Stores the next message bit to encode
            messageBit = (message[i] << j & 0x80)/0x80;
            nextByte = getc(file_ptr);
            if (nextByte == EOF) {
                fclose(outfile);
                remove(outputFile);
                errorAndExit("Cannot encode into an incomplete image", file_ptr);
            }

            // Encodes the message bit into the least significant of the byte read from the original image
            nextByte = (nextByte & 0xFE) | messageBit;
            putc(nextByte, outfile);
        }
    }

    // Write the remaining image to the output file
    while ((nextByte = fgetc(file_ptr)) != EOF) {
        fputc(nextByte, outfile);
    }

    fclose(outfile);
}

// Determines if the message can fit into the image
bool doesMessageFit(struct ImageInfo *info, char *message) {
    // The length of the message can't be stored in an int value. this is bad
    // strlen returns a size_t which isn't necessarily the same size and an int
    if ((strlen(message) + 1) > sizeof(int) * 8) {
        return false;
    }

    // extra 1 byte to store the null terminator
    int length = (int) strlen(message) + 1;

    // it takes 3 pixels to store all 8 bits of 1 character.
    return (length * 8) < (info->height * info->width * 3);
}

// Copies the header from the input image to the output image.
void copyHeader(FILE *file_ptr, FILE *outfile, struct ImageInfo *imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file_ptr);

    while ((nextByte = fgetc(file_ptr)) != EOF && charsCopied < imageInfo->pixelMapOffset)
    {
        if (nextByte == EOF) {
            errorAndExit("Unexpected end of file_ptr", file_ptr);
        }

        fputc(nextByte, outfile);
        charsCopied++;
    }

}
