//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_COMMON_H
#define ASS1_COMMON_H

#include <stdio.h>

struct ImageInfo {
    int width;
    int height;
    int depth;
    long pixelMapOffset;
};

enum ImageType {
    unsupported,
    ppm,
    bmp
};


enum ImageType getImageType(FILE *file);
void errorAndExit(char error[]);
void messageAndExit(char message[]);
void printImageInfo(struct ImageInfo *imageInfo);
#ifdef DEBUG
void printByteBits(int byte);
#endif

#endif //ASS1_COMMON_H
