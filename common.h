//
// Created by Sol Jennings on 13/3/17.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef ASS1_COMMON_H
#define ASS1_COMMON_H

struct ImageInfo {
    int width;
    int height;
    int depth;
    long imageMapPosition;
};

enum ImageType {
    unsupported,
    ppm,
    bmp
};

#endif //ASS1_COMMON_H

enum ImageType getImageType(FILE *file);

void errorAndExit(char error[]);

void printImageInfo(struct ImageInfo *imageInfo);

void printByteBits(int byte);
