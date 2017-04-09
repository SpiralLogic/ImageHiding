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

#include "common.h"
#include "commonHide.h"
#include "bmpCommon.h"
#include "ppmCommon.h"
#include "hide.h"

/**
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct encode function to encode the message into the image file.
*/
int main(int argc, char *argv[]) {

    if (strcmp(argv[1], "-m") == 0) {
        mSwitch(argc, argv);
    }
    else if (strcmp(argv[1], "-p") == 0) {
        pSwitch(argc, argv);
    }
    else if (strcmp(argv[1], "-s") == 0) {
        sSwitch(argc, argv);
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

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    inputFile = argv[1];
    outputFile = argv[2];

    MessageInfo messageInfo = createSecretMessageStruct(readFromInput());

    encodeMessageInFile(inputFile, outputFile, &messageInfo);

    freeSecretMessageStruct(&messageInfo);

    printf("\nSuccessfully hid message in %s!\n", outputFile);
}

/**
 * Handles the case where multiple files need to be used to hide a message
 *
 * @param argv original input parameters
 */
void mSwitch(int argc, char *argv[]) {
    int num_files;
    char *basename, *outputBasename, *readChar;
    char outputPath[PATH_MAX], inputPath[PATH_MAX];
    long conv;

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
        // No error
        num_files = conv;
    }

    if (num_files < 0) {
        errorAndExit("Must be at least 1 file to hide message in", NULL);
    } else if (num_files > 1000) {
        errorAndExit("Maximum number of files to hide in is 1000", NULL);
    }

    basename = argv[3];
    outputBasename = argv[4];

    for(int i=0; i<num_files; ++i) {

        sprintf(inputPath, "%s-%03d.ppm", basename, i);
        sprintf(outputPath, "%s-%03d.ppm", outputBasename, i);
        printf("%s\n", inputPath);
        printf("%s\n", outputPath);
    }
}

/**
 * Handles the case where parallel execution is used to hide the message
 *
 * @param argv original input parameters
 */
void pSwitch(int argc, char *argv[]) {
    char *inputFile;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    inputFile = argv[2];
    printf("%s", inputFile);
}

/**
 * Handles the case where the before and after image are shown
 *
 * @param argv original input parameters
 */
void sSwitch(int argc, char *argv[]) {

    if (argc != 4) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    char *noSwitchParameters[] = { argv[0], argv[2], argv[3]};
    printf("%s %s %s", noSwitchParameters[0],noSwitchParameters[1] ,noSwitchParameters[2]);
    noSwitch(3, noSwitchParameters);
}

/**
 * displays the use for this command
*/
void usage() {
    printf("\nUsage\n");
    printf("./hide inputimage outputfile\n");
}
