/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for unhiding a message in an image file
*/

#include "common.h"
#include "commonUnhide.h"
#include "unhide.h"

/**
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct decode function to decode the message from the image file.
*/
int main(int argc, char *argv[]) {
    char *imageFile;

    if (argc != 2) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageFile = argv[1];
    printf("##################\n");
    decodeImage(imageFile);
    printf("\n##################\n");

    return 0;
}

/**
 * displays the use for this command
*/
void usage() {
    printf("\nUsage\n");
    printf("./unhide filename\n");
}