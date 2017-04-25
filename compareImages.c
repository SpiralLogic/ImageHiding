/**
 * Created by Sol Jennings on 17/4/17.
 *
 * Functions for comparing 2 images to a user using SDL
 *
 * Images are compared with the original on the top and the encoded image on the bottom
 */

#include <memory.h>
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>

#include "compareImages.h"
#include "ppmCommon.h"
#include "bmpCommon.h"
#include "commonHide.h"
#include "common.h"

/**
 * Compares 2 images by displaying them on the screen with SDL
 *
 * @param image1 first image file to show
 * @param image2 second image file to show
 */
void compareImages(char *image1, char *image2) {
    SDL_Event Events;
    /* The window to render to */
    SDL_Window *window = NULL;
    /* The surface contained by the window */
    SDL_Surface *screenSurface = NULL;
    FILE *image1_ptr, *image2_ptr;
    enum ImageType imageType1, imageType2;
    ImageInfo *imageInfo1_ptr, *imageInfo2_ptr;
    ImageInfo imageInfo1, imageInfo2;
    bool windowOpen = true;

    // Get first image information
    image1_ptr = fopen(image1, "r");
    if (image1_ptr == NULL) {
        errorAndExit("Cannot open file", NULL);
    }

    // Get second image information
    image2_ptr = fopen(image2, "r");
    if (image2_ptr == NULL) {
        errorAndExit("Cannot open file", image1_ptr);
    }

    // Work out input image information
    imageType1 = getImageType(image1_ptr);
    imageType2 = getImageType(image2_ptr);

    if (imageType1 == unsupported || imageType2 == unsupported) {
        fclose(image1_ptr);
        fclose(image2_ptr);
        errorAndExit("Image type unsupported", NULL);
    }

    if (imageType1 != imageType2) {
        fclose(image1_ptr);
        fclose(image2_ptr);
        errorAndExit("Both images must be of same time", NULL);
    }

    if (imageType1 == ppm) {
        imageInfo1 = verifyAndGetPpmInfo(image1_ptr);
        imageInfo2 = verifyAndGetPpmInfo(image2_ptr);
    } else if (imageType1 == bmp) {
        imageInfo1 = verifyAndGetBmpInfo(image1_ptr);
        imageInfo2 = verifyAndGetBmpInfo(image2_ptr);
    }

    // Exit if either images info couldn't be read
    if (!imageInfo1.successRead) {
        fclose(image2_ptr);
        errorAndExit(imageInfo1.errorMesssage, image1_ptr);
    }

    if (!imageInfo2.successRead) {
        fclose(image1_ptr);
        errorAndExit(imageInfo2.errorMesssage, image2_ptr);
    }

    imageInfo1_ptr = &imageInfo1;
    imageInfo1_ptr->filename = image1;
    imageInfo2_ptr = &imageInfo2;
    imageInfo2_ptr->filename = image2;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        errorAndExit("SDL could not initialize!", image1_ptr);
    } else {
        // Surface width will be the size of the images on top of each other
        int surfaceHeight = imageInfo1_ptr->height + imageInfo2_ptr->height;
        int surfaceWidth = imageInfo1_ptr->width > imageInfo2_ptr->width ?
                           imageInfo1_ptr->width : imageInfo2_ptr->width;

        /* Create the window */
        window = SDL_CreateWindow("Original Top / Encoded Bottom",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  surfaceWidth,
                                  surfaceHeight,
                                  SDL_WINDOW_SHOWN);

        if (window == NULL) {
            errorAndExit("Window could not be created!", image1_ptr);
        } else {
            /* Get screen surface */
            screenSurface = SDL_GetWindowSurface(window);

            drawImage(screenSurface, image1_ptr, imageInfo1_ptr, 0, 0);
            drawImage(screenSurface, image2_ptr, imageInfo2_ptr, 0, imageInfo2_ptr->height);
            /* Update the screen */
            SDL_UpdateWindowSurface(window);
            while (windowOpen) {
                while (SDL_PollEvent(&Events)) {
                    if (Events.type == SDL_QUIT || Events.type == SDL_KEYDOWN)
                        windowOpen = false;
                }

            }
        }

        /* Destroy the window */
        SDL_FreeSurface(screenSurface);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    fclose(image1_ptr);
    fclose(image2_ptr);
}

/**
 * Draws the image to the surface starting for the coordinates specified. Coordinates are
 * used for when the image should be draw side by side of on top of each other
 * @param surface       SDL surface to draw image on
 * @param image_ptr     Pointer to the image file
 * @param imageInfo_ptr Information about the image
 * @param startX        X Position to start the image
 * @param startY        Y Position to start the image
 */
void drawImage(SDL_Surface *surface, FILE *image_ptr, ImageInfo *imageInfo_ptr, int startX, int startY) {
    int r, g, b;

    // move to the pixel map -1 so the first byte is the the first of the image map
    fseek(image_ptr, imageInfo_ptr->pixelMapOffset, SEEK_SET - 1);

    for (int y=startY; y < imageInfo_ptr->height + startY; y++) {
        for (int x=startX; x < imageInfo_ptr->width + startX; x++) {
            r=fgetc(image_ptr);
            g=fgetc(image_ptr);
            b=fgetc(image_ptr);
            drawPixel(surface, x, y, r, g, b);
        }
    }
}

/**
 * Draws a pixel to an SDL Surface
 *
 * @param surface   SDL surface
 * @param x         x position
 * @param y         y position
 * @param r         red pixel
 * @param g         green pixel
 * @param b         blue pixel
 */
void drawPixel(SDL_Surface *surface, int x, int y, int r, int g, int b) {
    /* Make p point to the place we want to draw the pixel */
    int *p = (int *) surface->pixels + y * surface->pitch/surface->format->BytesPerPixel + x;

    /* Draw the pixel! */
    *p = SDL_MapRGB(surface->format, r, g, b);
}