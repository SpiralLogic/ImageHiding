//
// Created by Sol Jennings on 13/3/17.
//

// Main executable for hiding a message in an image file
#include <stdlib.h>
#include <string.h>

#include "ppmHide.h"
#include "bmpHide.h"
#include "common.h"
#include "commonHide.h"
#include "hide.h"

// Parses input arguments to make sure they are valid, determines the input file and then uses the
// correct encode function to encode the message into the image file.
int main(int argc, char *argv[]) {
    char *imageFile;
    char *outputFile;
    enum ImageType imageType;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageFile = argv[1];
    outputFile = argv[2];

    FILE *file_ptr = fopen(imageFile, "r");

    if (file_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    imageType = getImageType(file_ptr);

    if (imageType == unsupported) {
        errorAndExit("Image type unsupported", file_ptr);
    }

    setSecretMessage(readFromInput());

    if (imageType == ppm) {
        hideInPpm(file_ptr, outputFile, getSecretMessage());
        freeSecretMessage();
        messageAndExit("Successfully hid message in PPM!", file_ptr);
    } else if (imageType == bmp) {
        hideInBmp(file_ptr, outputFile, getSecretMessage());
        freeSecretMessage();
        messageAndExit("Successfully hid message in BMP!", file_ptr);
    }

    return 0;
}

// displays the use for this command
void usage() {
    printf("\nUsage\n");
    printf("./hide inputimage outputfile\n");
}

// Reads a set of characters from the standard in until an EOF/Ctrl+D is reached
char* readFromInput() {
    char buffer[BUFF_SIZE];
    size_t inputSize = 1; // includes NULL

    /* Preallocate space.  We could just allocate one char here,
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