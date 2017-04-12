/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains the common functionality required to hide an image
*/
#include <memory.h>
#include <stdlib.h>
#include "commonHide.h"
#include "ppmCommon.h"
#include "bmpCommon.h"
/**
 * Encodes a message into a 24 bit pixel map
 * Each RGB colour in a pixel will store 1 bit of the message in it's least significant bit
 */
void encodeMessageInFile(char *inputFile, char *outputFile, MessageInfo *messageInfo) {
    FILE *outfile_ptr, *inputFile_ptr;
    enum ImageType imageType;
    struct ImageInfo *imageInfo_ptr;
    struct ImageInfo imageInfo;
    int nextByte;

    inputFile_ptr = fopen(inputFile, "r");

    if (inputFile_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    // Work out input image information
    imageType = getImageType(inputFile_ptr);
    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", inputFile_ptr);
    }

    if (imageType == ppm) {
        imageInfo = verifyAndGetPpmInfo(inputFile_ptr);
    } else if (imageType == bmp) {
        imageInfo = verifyAndGetBmpInfo(inputFile_ptr);
    }

    imageInfo_ptr = &imageInfo;
    imageInfo_ptr->filename = inputFile;

    size_t imageSize = imageInfo_ptr->height * imageInfo_ptr->width * 3;

    // Remove output file if it exists and attempted to output
    remove(outputFile);
    outfile_ptr = fopen(outputFile, "w+");

    if (outfile_ptr == NULL) {
        errorAndExit("Cannot open output file", inputFile_ptr);
    }

    copyHeader(inputFile_ptr, outfile_ptr, imageInfo_ptr);

    //Set to the start of the pixel map
    fseek(inputFile_ptr, imageInfo_ptr->pixelMapOffset, SEEK_SET);

    if (messageInfo->hideMode == single && messageInfo->length * 8 > imageSize) {
        fclose(outfile_ptr);
        remove(outputFile);
        freeSecretMessageStruct(messageInfo);
        errorAndExit("Message too big for image", inputFile_ptr);
    }

    // encode the message into the image and output it a byte at a time to the file
    for (size_t i = messageInfo->currentPos; i < messageInfo->length; i++) {
        printf("%zu %zu %zu %zu\n", i, imageSize, messageInfo->currentPos, messageInfo->length);
        // Stop if no more of the message can be hidden in the image
        if ((i + 1 - messageInfo->currentPos) * 8 >= imageSize && messageInfo->hideMode == multiple) {
            messageInfo->currentPos = i;
            fclose(inputFile_ptr);
            fclose(outfile_ptr);
            return;
        }

        nextByte = messageInfo->message[i];
        printf("hiding %c\n", nextByte);
        encodeByteToOutput(nextByte, inputFile_ptr, outfile_ptr, outputFile, messageInfo);
    }

    // finished hiding message in images so just copy over pixel maps for remaining images
    messageInfo->currentPos = messageInfo->length;

    // Write the remaining image to the output file
    while ((nextByte = fgetc(inputFile_ptr)) != EOF) {
        fputc(nextByte, outfile_ptr);
    }

    fclose(inputFile_ptr);
    fclose(outfile_ptr);
}

/**
 * takes in one byte, encodes that byte into the next 8 bytes of the input file and writes
 * it to the output file
*/
void encodeByteToOutput(int byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile, MessageInfo *messageInfo) {
    int messageBit, nextByte;

    for (int i = 0; i < 8; i++) {
        // Stores the next message bit to encode
        messageBit = ((byte) << i & 0x80) / 0x80;
        nextByte = fgetc(file_ptr);

        if (nextByte == EOF) {
            fclose(outfile_ptr);
            remove(outputFile);
            freeSecretMessageStruct(messageInfo);
            errorAndExit("Cannot encode into incomplete image", file_ptr);
        }

        // Encodes the message bit into the least significant of the byte read from the original image
        nextByte = (nextByte & 0xFE) | messageBit;

        if (fputc(nextByte, outfile_ptr) == EOF || ferror(outfile_ptr)) {
            fclose(outfile_ptr);
            remove(outputFile);
            freeSecretMessageStruct(messageInfo);
            errorAndExit("Error writing to output file", file_ptr);
        }
    }
}

/**
 * Copies the header from the input image to the output image.
*/
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo_ptr) {
    int nextByte;
    long charsCopied = 0;

    rewind(file_ptr);

    // copy each byte until the pixel map of the image is reached
    while ((nextByte = fgetc(file_ptr)) != EOF && charsCopied < imageInfo_ptr->pixelMapOffset) {
        fputc(nextByte, outfile_ptr);
        charsCopied++;
    }
}


/**
 * Set's the current secret message
 * @param message pointer
 */
MessageInfo createSecretMessageStruct(char *message) {
    MessageInfo messageInfo = { .message = message, .currentPos = 0, .length = strlen(message) };

    return messageInfo;
}

/**
 * Frees the memory allocated to the secret message
 */
void freeSecretMessageStruct(MessageInfo *messageInfo) {
    if (messageInfo != NULL) {
        if (messageInfo->message != NULL) {
            free(messageInfo->message);
            messageInfo->message = NULL;
        }
        messageInfo = NULL;
    }
}



/**
 * Reads a set of characters from the standard in until an EOF/Ctrl+D is reached
 */
char* readFromInput() {
    char buffer[BUFF_SIZE];
    size_t inputSize = 1; // includes NULL

    /** Preallocate space.  We could just allocate one char here,
    but that wouldn't be efficient. */
    char *input = malloc(sizeof(char) * BUFF_SIZE);

    if(input == NULL)
    {
        errorAndExit("Failed to allocate content", NULL);
    } else
    {
        input[0] = '\0'; // make null-terminated
    }

    // Dunno why sometimes I need to use 3
    printf("Input secret message press ctrl+D 1-3 times when finished\n");

    // Keep reading a buffer sized amount of characters until EOF is reached
    while(fgets(buffer, BUFF_SIZE, stdin))
    {
        char *old = input;
        inputSize += strlen(buffer);

        // We need more memory!
        input = realloc(input, inputSize);

        if(input == NULL)
        {
            free(old);
            errorAndExit("Couldn't allocate anymore space for message", NULL);
        }
        strcat(input, buffer);
    }

    // Oh no!
    if(ferror(stdin))
    {
        free(input);
        errorAndExit("Error reading from stdin.", NULL);
    }

    //returns the pointer to the read in string
    return input;
}