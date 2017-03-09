#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IMAGE_DEPTH 255
#define MAX 512

int getNextCharacter(FILE *fp);
void printIntAsBinary(int c);
void processFile(char *filename, char *message);
void errorAndExit(char error[]);
enum ImageType getImageType(FILE *file);
int moveOverAndCountComments(FILE *file);
struct ImageInfo getImageInfo(FILE *file);
void moveFileToNextLine(FILE *file);
int scanDimension(FILE *file);

bool doesMessageFit(struct ImageInfo info, char *message);

void encodeImage(FILE *file, struct ImageInfo info, int numComments, char *message);

void copyHeader(FILE *file, FILE *outfile, int comments);

enum ImageType {
    unsupported,
    ppm,
    bmp
};

struct ImageInfo {
    int width;
    int height;
    int depth;
};

int main(int argc, char *argv[]) {
    char *secretMessage;
    char *imageFile;

    if (argc < 3) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];
    secretMessage = argv[2];

    processFile(imageFile, secretMessage);

    return 0;
}

enum ImageType getImageType(FILE *file) {
    enum ImageType imageType = unsupported;

    rewind(file);

    if (getc(file) == 'P' && getc(file) == '6') {
        imageType = ppm;
    }

    return imageType;
}

void processFile(char *filename, char *message) {
    int c;
    int numComments;
    struct ImageInfo imageSize;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    if (getImageType(file) == unsupported) {
        errorAndExit("Image type unsupported");
    }

    numComments = 0;

    imageSize = getImageInfo(file);

    if (imageSize.depth != MAX_IMAGE_DEPTH) {
        errorAndExit("Image colour depth must be 255");
    }

    if (!doesMessageFit(imageSize, message)) {
        errorAndExit("Message does not fit image");
    }

    printf("width %d\n", imageSize.width);
    printf("height %d\n", imageSize.height);
    printf("depth %d\n", imageSize.depth);

    encodeImage(file, imageSize, numComments, message);

    fclose(file);
}

void encodeImage(FILE *file, struct ImageInfo info, int numComments, char *message) {
    FILE *outfile = fopen("outfile.ppm", "w+");
    copyHeader(file, outfile, numComments);
    int messageLength = (int) strlen(message) + 1;

    for (int i=0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d", (message[i] << j & 0x80)/0x80) ;
        }
        printf("\n");
    }

    fclose(outfile);
}

void copyHeader(FILE *file, FILE *outfile, int comments) {
    char line[MAX];
    int linesCopied=0;
    rewind(file);

    while (fgets(line,sizeof(line),file) != NULL && linesCopied < comments + 3)
    {
        /*Write the line */
        fputs(line, outfile);
        linesCopied++;
    }
}

bool doesMessageFit(struct ImageInfo info, char *message) {

    if (strlen(message) > sizeof(int) * 8) {
        return false;
    }

    int length = (int) strlen(message) + 1;

    return (length * 8) < (info.height * info.width * 3);
}

int moveOverAndCountComments(FILE *file) {
    int currentChar;
    int count = 0;
    while ((currentChar = getc(file)) == '#') {
        count++;
        moveFileToNextLine(file);
    }

    ungetc(currentChar, file);

    return count;
}

struct ImageInfo getImageInfo(FILE *file) {
    struct ImageInfo imageInfo;
    bool headerComplete = false;
    int nextChar;
    int currentDimension = 0;
    int dimensionValue;

    while (!headerComplete) {
        nextChar = getc(file);
        printf("%c\n", nextChar);
        ungetc(nextChar, file);
        getchar();
        if (nextChar == '#') {
            moveFileToNextLine(file);
            continue;
        }
        dimensionValue = scanDimension(file);

        if (dimensionValue > 0) {
            switch (currentDimension) {
                case 0:
                    imageInfo.width = dimensionValue;
                    currentDimension++;
                    break;
                case 1:
                    imageInfo.height = dimensionValue;
                    currentDimension++;
                    break;
                case 2:
                    imageInfo.depth = dimensionValue;
                    headerComplete = true;
                    break;
                default:
                    errorAndExit("wtf");
            }

        }
        printf("%d %d %d\n", imageInfo.height, imageInfo.width, imageInfo.depth);

    }

    return imageInfo;
}

int scanDimension(FILE *file) {
    int dimension;
    if (fscanf(file, "%d", &dimension) == 0) {
        return -1;
    }
    printf("scanned %d\n", dimension);
    return dimension;
}


void moveFileToNextLine(FILE *file) {
    while (getc(file) != '\n');
}

void errorAndExit(char error[]) {
    printf("Error: %s\n", error);
    exit(1);
}

