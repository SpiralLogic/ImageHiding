//
// Created by Sol Jennings on 17/4/17.
//

#ifndef ASS2_COMPAREIMAGES_H
#define ASS2_COMPAREIMAGES_H

#include "common.h"

#include <SDL.h>


void compareImages(char *imageFile, char *image2);
void drawImage(SDL_Surface *surface, FILE *image_ptr, ImageInfo *imageInfo);
void drawPixel(SDL_Surface *surface, int x, int y, int r, int g, int b);

#endif //ASS2_COMPAREIMAGES_H
