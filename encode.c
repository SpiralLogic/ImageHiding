#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int getNextCharacter(FILE *fp);
void printIntAsBinary(int c);
void processFile(char *filename);
void errorAndExit(char error[]);
void processMessage(char *message);
enum ImageType getImageType(FILE *file);
void skipImageComments(FILE *file);
struct ImageSize getImageSize(FILE *file);
void moveFileToNextLine(FILE *file);

enum ImageType {
    unsupported,
    ppm,
    bmp
};

struct ImageSize {
    int width;
    int height;
};

int main(int argc, char *argv[]) {
    char *secretMessage;
    char *imageFile;

    if (argc < 3) {
        errorAndExit("Not enough arguments passed");
    }

    imageFile = argv[1];
    secretMessage = argv[2];

    processFile(imageFile);
  //  processMessage(secretMessage);

    return 0;
}

void processMessage(char *message) {
    for (int i=0; i <= sizeof(message); i++) {
        printIntAsBinary(message[i]);
    }
}

enum ImageType getImageType(FILE *file) {
    enum ImageType imageType = unsupported;

    rewind(file);

    if (getc(file) == 'P' && getc(file) == '6') {
        imageType = ppm;
    }

    while(getc(file) != '\n');

    return imageType;
}

void processFile(char *filename) {
    int c;
    struct ImageSize imageSize;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        errorAndExit("Cannot open file");
    }

    if (getImageType(file) == unsupported) {
        errorAndExit("Image type unsupported");
    }

    skipImageComments(file);
    imageSize = getImageSize(file);

    printf("width %d", imageSize.width);
    printf("height %d", imageSize.height);

    while((c = getNextCharacter(file)) != '\n') {
        printf("%c", c);
        //printIntAsBinary(c);
    }

    fclose(file);
}

void skipImageComments(FILE *file) {
    int currentChar;

    while ((currentChar = getc(file)) == '#') {
        moveFileToNextLine(file);
    }

    ungetc(currentChar, file);
}

struct ImageSize getImageSize(FILE *file) {
    struct ImageSize imageSize;

    fscanf(file, "%d %d", &imageSize.width, &imageSize.height);
    return imageSize;
}

int getNextCharacter(FILE *file) {
    int c = getc(file);
    return c;
}

void printIntAsBinary(int c) {
    int i;
    for (i = 0; i < 8; i++) {
        printf("%d", ((c << i) & 0x80) != 0);
    }

    printf("\n");
}
void moveFileToNextLine(FILE *file) {
    while (getc(file) != '\n');
}

void errorAndExit(char error[]) {
    printf("Error: %s", error);
    exit(1);
}

