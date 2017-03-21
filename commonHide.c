//
// Created by Sol Jennings on 13/3/17.
//
// Contains the common functionality required to hide an image

#include <memory.h>
#include <stdlib.h>
#include "commonHide.h"

// The secret message pointer. Stored here so that it can be set free later!
static char *secretMessage;

// Encodes a message into a 24 bit pixel map
// Each RGB colour in a pixel will store 1 bit of the message in it's least significant bit
void encodeImage(FILE *file_ptr, struct ImageInfo *imageInfo, char *outputFile, char *message) {
    remove(outputFile);

    FILE *outfile_ptr = fopen(outputFile, "w+");

    if (outfile_ptr == NULL) {
        freeSecretMessage();
        errorAndExit("Cannot open output file", file_ptr);
    }

    copyHeader(file_ptr, outfile_ptr, imageInfo);

    //Set to the start of the pixel map
    fseek(file_ptr, imageInfo->pixelMapOffset, SEEK_SET);

    int messageLength = (int) strlen(message) + 1;
    int messageBit;
    int nextByte;

    // encode the message into the image and output it a byte at a time to the file
    for (int i=0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {

            // Stores the next message bit to encode
            messageBit = (message[i] << j & 0x80)/0x80;
            nextByte = getc(file_ptr);

            if (nextByte == EOF) {
                //Where is the rest of the image!
                fclose(outfile_ptr);
                remove(outputFile);
                freeSecretMessage();
                errorAndExit("Cannot encode into an incomplete image", file_ptr);
            }

            // Encodes the message bit into the least significant of the byte read from the original image
            nextByte = (nextByte & 0xFE) | messageBit;
            putc(nextByte, outfile_ptr);
        }
    }

    // Write the remaining image to the output file
    while ((nextByte = fgetc(file_ptr)) != EOF) {
        fputc(nextByte, outfile_ptr);
    }

    fclose(outfile_ptr);
    printf("Output image: %s\n", outputFile);
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
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo) {
    int nextByte;
    long charsCopied = 0;

    rewind(file_ptr);

    while ((nextByte = fgetc(file_ptr)) != EOF && charsCopied < imageInfo->pixelMapOffset)
    {
        if (nextByte == EOF) {
            freeSecretMessage();
            errorAndExit("Unexpected end of file_ptr", file_ptr);
        }

        fputc(nextByte, outfile_ptr);
        charsCopied++;
    }

}


// sets the current secret message
void setSecretMessage(char *message) {
    secretMessage = message;
}

// Gets the current secret message
char *getSecretMessage(){
    return secretMessage;
}

// frees the memory held by the secret message
void freeSecretMessage() {
    if (secretMessage != NULL) {
        free(secretMessage);
        secretMessage = NULL;
    }
}


