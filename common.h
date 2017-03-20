//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_COMMON_H
#define ASS1_COMMON_H

#include <stdio.h>
#include <stdbool.h>

struct ImageInfo {
    int width;
    int height;
    int depth;
    long pixelMapOffset;
    bool successRead;
    char* errorMesssage;
};

enum ImageType {
    unsupported,
    ppm,
    bmp
};


enum ImageType getImageType(FILE *file_ptr);
void errorAndExit(char *error, FILE *file_ptr);
void messageAndExit(char *message, FILE *file_ptr);
void printImageInfo(struct ImageInfo *imageInfo);
#ifdef DEBUG
void printByteBits(int byte);
#endif

#endif //ASS1_COMMON_H
