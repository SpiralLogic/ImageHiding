//
// Created by Sol Jennings on 13/3/17.
//
// Contains the common functionality required to hide an image
#include <memory.h>
#include <stdlib.h>
#include "commonHide.h"

// Encodes a message into a 24 bit pixel map
// Each RGB colour in a pixel will store 1 bit of the message in it's least significant bit
void readAndEnocdeMessage(FILE *file_ptr, struct ImageInfo *imageInfo, char *outputFile) {
    // Start with 1 byte for null terminator
    size_t messageLength = 1, imageSize = imageInfo->height * imageInfo->width * 3;
    int nextByte, inputChar;

    remove(outputFile);
    FILE *outfile_ptr = fopen(outputFile, "w+");

    if (outfile_ptr == NULL) {
        errorAndExit("Cannot open output file", file_ptr);
    }

    copyHeader(file_ptr, outfile_ptr, imageInfo);

    //Set to the start of the pixel map
    fseek(file_ptr, imageInfo->pixelMapOffset, SEEK_SET);
    printf("Input secret message press ctrl+D 1-3 times when finished\n");

    // encode the message into the image and output it a byte at a time to the file
    while ((inputChar = getc(stdin)) != EOF) {
        // Oh no!
        if(ferror(stdin))
        {
            fclose(outfile_ptr);
            errorAndExit("Error reading from stdin.", NULL);
        }

        messageLength++;

        if (messageLength * 8 > imageSize) {
            fclose(outfile_ptr);
            remove(outputFile);
            errorAndExit("Message too big for image", file_ptr);
        }
        encodeByteToOutput(&inputChar, file_ptr, outfile_ptr, outputFile);
    }

    inputChar = '\0';

    // Add null terminator
    encodeByteToOutput(&inputChar, file_ptr, outfile_ptr, outputFile);

    // Write the remaining image to the output file
    while ((nextByte = fgetc(file_ptr)) != EOF) {
        fputc(nextByte, outfile_ptr);
    }

    fclose(outfile_ptr);
}

// takes in one byte, encodes that byte into the next 8 bytes of the input file and writes
// it to the output file
void encodeByteToOutput(int *byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile) {
    int messageBit, nextByte;

    for (int i = 0; i < 8; i++) {
        // Stores the next message bit to encode
        messageBit = ((*byte) << i & 0x80)/0x80;
        nextByte = fgetc(file_ptr);

        if (nextByte == EOF) {
            fclose(outfile_ptr);
            remove(outputFile);
            errorAndExit("Cannot encode into incomplete image", file_ptr);
        }

        // Encodes the message bit into the least significant of the byte read from the original image
        nextByte = (nextByte & 0xFE) | messageBit;
        if (fputc(nextByte, outfile_ptr) == EOF || ferror(outfile_ptr)) {
            fclose(outfile_ptr);
            remove(outputFile);
            errorAndExit("Error writing to output file", file_ptr);
        }
    }
}

// Copies the header from the input image to the output image.
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file_ptr);

    while ((nextByte = fgetc(file_ptr)) != EOF && charsCopied < imageInfo->pixelMapOffset)
    {
        if (nextByte == EOF) {
            errorAndExit("Unexpected end of file_ptr", file_ptr);
        }

        fputc(nextByte, outfile_ptr);
        charsCopied++;
    }

}