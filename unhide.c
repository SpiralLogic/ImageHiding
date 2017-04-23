/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for unhiding a message in an image file
*/

#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "common.h"
#include "commonUnhide.h"
#include "unhide.h"

/**
 * Parses input arguments to make sure they are valid, determines the input file and then uses the
 * correct decode function to decode the message from the image file.
 *
 * @param argc number of input arguments
 * @param argv input argument array
*/
int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage();
        return 1;
    }
    if (strcmp(argv[1], "-d") == 0) {
        dSwitch(argc, argv);
    } else if (strcmp(argv[1], "-m") == 0) {
        mSwitch(argc, argv);
    } else {
        noSwitch(argc, argv);
    }

    return 0;
}

/**
 * Handles the case where no switches are given
 *
 * @param argc original argument count
 * @param argv original input parameters
 * */
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

 * @param argc original argument count
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
    printf("##################\n");

    while (1) {
        sprintf(inputPath, "%s-%03d.ppm", basename, i);
        // if the file exists read message from it
        if (access(inputPath, R_OK) != -1) {
            if (decodeImage(inputPath)) {
                printf("\n##################\n");
                break;
            }
        } else {
            fprintf(stderr, "Could not read image file: %s", inputPath);
            exit(1);
        }
        i++;
    }
}

/**
 * Switch for decoding an entire directory of images
 *
 * @param argc original argument count
 * @param argv original input parameters
 */
void dSwitch(int argc, char *argv[]) {
    char *imageDirectory;
    DIR *imageDirectory_ptr;
    char inputImage[PATH_MAX];
    struct dirent *dir;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageDirectory = argv[2];

    imageDirectory_ptr = opendir(imageDirectory);

    if (imageDirectory_ptr == NULL) {
        fprintf(stderr, "\nCould not open directory: %s\n", imageDirectory);
        exit(1);
    }

    printf("##################\n");

    while ((dir = readdir(imageDirectory_ptr)) != NULL) {
        if (dir->d_type != DT_DIR) {
            sprintf(inputImage, "%s/%s", imageDirectory, dir->d_name);
            if (decodeImage(inputImage)) {
                break;
            }
        }
    }

    printf("\n##################\n");
    closedir(imageDirectory_ptr);
}

/**
 * displays the use for this command
*/
void usage() {
    printf("\nUsage\n");
    printf("./unhide filename\n");
    printf("./unhide -m basename\n");
    printf("./unhide -d directory\n");
}