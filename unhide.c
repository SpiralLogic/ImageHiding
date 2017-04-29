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
    decodeImage(imageFile, false);

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

    while (1) {
        sprintf(inputPath, "%s-%03d.ppm", basename, i);
        // if the file exists read message from it
        if (access(inputPath, R_OK) != -1) {
            if (decodeImage(inputPath, false)) {
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
    struct dirent **fileList;
    int numberOfFiles;

    if (argc != 3) {
        usage();
        errorAndExit("Incorrect number of parameters passed", NULL);
    }

    imageDirectory = argv[2];

    numberOfFiles = scandir(imageDirectory, &fileList, 0, alphasort);

    if (numberOfFiles < 0) {
        errorAndExit("Could not read input directory", NULL);
    }

    for (int i = 0; i < numberOfFiles; i++) {
        if (fileList[i]->d_type != DT_DIR) {
            snprintf(inputImage, PATH_MAX, "%s/%s", imageDirectory, fileList[i]->d_name);
            if (decodeImage(inputImage, true)) {
                break;
            }
        }
        free(fileList[i]);
    }

    free(fileList);

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