/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for unhiding a message in an image file
*/
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "commonUnhide.h"
#include "unhide.h"

/**
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct decode function to decode the message from the image file.
*/
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-m") == 0) {
        mSwitch(argc, argv);
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
    char *imageFile;

    if (argc != 2) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageFile = argv[1];
    printf("##################\n");
    decodeImage(imageFile);
    printf("\n##################\n");

}

/**
 * Handles the case where multiple files need to be used to hide a message
 *
 * @param argv original input parameters
 */
void mSwitch(int argc, char *argv[]) {
    char *basename;
    char inputPath[PATH_MAX];

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    basename = argv[2];
    int i = 0;
    while (1) {
        sprintf(inputPath, "%s-%03d.ppm", basename, i);
        if (access(inputPath, R_OK) != -1 ) {
            decodeImage(inputPath);
        } else {
            return;
        }
        i++;
    }
}

/**
 * displays the use for this command
*/
void usage() {
    printf("\nUsage\n");
    printf("./unhide filename\n");
}