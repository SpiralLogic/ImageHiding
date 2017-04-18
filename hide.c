/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for hiding a message in an image file
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

#include "common.h"
#include "commonHide.h"
#include "compareImages.h"
#include "bmpCommon.h"
#include "ppmCommon.h"
#include "hide.h"

/**
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct encode function to encode the message into the image file.
*/
int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage();
        return 1;
    }
    if (strcmp(argv[1], "-m") == 0) {
        mSwitch(argc, argv);
    } else if (strcmp(argv[1], "-p") == 0) {
        pSwitch(argc, argv);
    } else if (strcmp(argv[1], "-s") == 0) {
        sSwitch(argc, argv);
    } else if (strcmp(argv[1], "-f") == 0) {
        fSwitch(argc, argv);
    } else {
        noSwitch(argc, argv);
    }

    return 0;
}

/**
 * Handles the case where no switches are given
 *
 * @param argv original input parameters
 */
void noSwitch(int argc, char *argv[]) {
    char *inputFile;
    char *outputFile;
    MessageInfo *messageInfo;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    inputFile = argv[1];
    outputFile = argv[2];

    // Dunno why sometimes I need to use 3
    printf("Input secret message press ctrl+D 1-3 times when finished\n");

    messageInfo = readFromInput();
    messageInfo->hideMode = single;

    encodeMessageInFile(inputFile, outputFile, messageInfo);

    freeSecretMessageStruct(messageInfo);

    printf("\nSuccessfully hid message in %s!\n", outputFile);
}

/**
 * Handles the case where multiple files need to be used to hide a message
 *
 * @param argv original input parameters
 */
void mSwitch(int argc, char *argv[]) {
    int num_files = 0;
    char *basename, *outputBasename, *readChar;
    char outputPath[PATH_MAX], inputPath[PATH_MAX];
    long conv;
    MessageInfo *messageInfo;

    if (argc != 5) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    errno = 0;
    conv = strtol(argv[2], &readChar, 10);

    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || *readChar != '\0' || conv > INT_MAX) {
        errorAndExit("Incorrect parameters, second needs to be an int", NULL);
    } else {
        num_files = conv;
    }

    if (num_files < 0) {
        errorAndExit("Must be at least 1 file to hide message in", NULL);
    } else if (num_files > 1000) {
        errorAndExit("Maximum number of files to hide in is 1000", NULL);
    }

    basename = argv[3];
    outputBasename = argv[4];

    messageInfo = readFromInput();
    messageInfo->hideMode = multiple;

    for(int i=0; i<num_files; ++i) {
        sprintf(inputPath, "%s-%03d.ppm", basename, i);
        sprintf(outputPath, "%s-%03d.ppm", outputBasename, i);

        printf("Hiding into: %s\n", inputPath);
        printf("Output as: %s\n", outputPath);
        encodeMessageInFile(inputPath, outputPath, messageInfo);
    }

    if (messageInfo->currentPos < messageInfo->length) {
        errorAndExit("Could not hide complete message in image", NULL);
    }
}

/**
 * Handles the case where parallel execution is used to hide the message
 *
 * @param argv original input parameters
 */
void pSwitch(int argc, char *argv[]) {
    char *inputFile;
    FILE *inputFile_ptr;
    char textFile[PATH_MAX], inputImage[PATH_MAX], outputImage[PATH_MAX];

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    inputFile = argv[2];
    inputFile_ptr = fopen(inputFile, "r");

    if (inputFile_ptr == NULL) {
        errorAndExit("Could not open input text file", NULL);
    }

    while (fscanf(inputFile_ptr, "%s %s %s", textFile, inputImage, outputImage) == 3) {

        pid_t pid = fork();

        if (pid == -1) {
            errorAndExit("Couldn't fork", inputFile_ptr);
        }

        if (pid == 0) {
            char *arguments[5] = { argv[0], "-f", textFile, inputImage, outputImage };
            int returnint = execv(arguments[0], arguments);
            printf("%d\n", returnint);
            exit(0);
        }
    }
    if (ferror(inputFile_ptr)) {
        errorAndExit("Error reading input file", inputFile_ptr);
    }

    fclose(inputFile_ptr);
    printf("\n Finished encoding into images\n");
    exit(0);
}

/**
 * Handles the case where the before and after image are shown
 *
 * @param argc original argument count
 * @param argv original input parameters
 */
void sSwitch(int argc, char *argv[]) {
    char *inputFile;
    char *outputFile;
    MessageInfo *messageInfo;

    if (argc != 4) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    inputFile = argv[2];
    outputFile = argv[3];

    // Dunno why sometimes I need to use 3
    printf("Input secret message press ctrl+D 1-3 times when finished\n");

    messageInfo = readFromInput();
    messageInfo->hideMode = single;

    encodeMessageInFile(inputFile, outputFile, messageInfo);
    freeSecretMessageStruct(messageInfo);

    printf("\nSuccessfully hid message in %s!\n", outputFile);

    compareImages(inputFile, outputFile);
}

/**
 * Used for parallel processing. Allows a message to be read from a file instead of stdin
 *
 * @param argc original argument count
 * @param argv original input parameters
 */
void fSwitch(int argc, char *argv[]) {
    char *messageFile;
    char *inputFile;
    char *outputFile;
    MessageInfo *messageInfo;
    FILE* messageFile_ptr;

    if (argc != 5) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    messageFile = argv[2];
    inputFile = argv[3];
    outputFile = argv[4];

    messageFile_ptr = fopen(messageFile, "r");

    if (messageFile_ptr == NULL) {
        errorAndExit("Could not open input text file", NULL);
    }

    dup2(fileno(messageFile_ptr), STDIN_FILENO);

    messageInfo = readFromInput();
    messageInfo->hideMode = single;

    fclose(messageFile_ptr);

    encodeMessageInFile(inputFile, outputFile, messageInfo);
    freeSecretMessageStruct(messageInfo);

    printf("\nSuccessfully hid message in %s!\n", outputFile);
}

/**
 * displays the use for this executable
*/
void usage() {
    printf("\nUsage\n");
    printf("./hide inputimage outputfile\n");
    printf("./hide -m numfiles base outputbase\n");
    printf("./hide -s inputimage outputfile\n");
    printf("./hide -p input file\n");
}
