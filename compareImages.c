/**
 * Created by Sol Jennings on 17/4/17.
 *
 * Functions for comparing 2 images to a user using SDL
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

/* Setting up screen size*/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
        int surfaceHeight = imageInfo1_ptr->height + imageInfo2_ptr->height;
        int surfaceWidth = imageInfo1_ptr->width > imageInfo2_ptr->width ?
                           imageInfo1_ptr->width : imageInfo2_ptr->width;

        /* Create the window */
        window = SDL_CreateWindow("Hello Window",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  surfaceWidth,
                                  surfaceHeight,
                                  SDL_WINDOW_SHOWN);

        if (window == NULL) {
            errorAndExit("Window could not be created!", image1_ptr);
        } else {
            /* Get screen surface */
            screenSurface = SDL_GetWindowSurface(window);

            /* Fill surface with white */
          //  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

            drawImage(screenSurface, image1_ptr, imageInfo1_ptr);
            /* Update the screen */
            SDL_UpdateWindowSurface(window);
            while (windowOpen) {
                while (SDL_PollEvent(&Events)) {
                    if (Events.type == SDL_QUIT)
                        windowOpen = false;
                }

            }
        }

        /* Destroy the window */
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void drawImage(SDL_Surface *surface, FILE *image_ptr, ImageInfo *imageInfo) {
    int r, g, b;
    fseek(image_ptr, imageInfo->pixelMapOffset, SEEK_SET - 1);

    for (int i=0; i < imageInfo->height; i++) {
        for (int j=0; j < imageInfo->width; j++) {
            r=fgetc(image_ptr);
            g=fgetc(image_ptr);
            b=fgetc(image_ptr);
            drawPixel(surface, j, i, r, g, b);
        }
    }
}

void drawPixel(SDL_Surface *surface, int x, int y, int r, int g, int b) {
    /* Make p point to the place we want to draw the pixel */
    printf("%d %d %d\n", r, g, b);
    int *p = (int *) surface->pixels + y * surface->pitch/4 + x * (surface->format->BytesPerPixel /4);

   // printf("", surface->)
    /* Draw the pixel! */
    *p = SDL_MapRGB(surface->format, r, g, b);
}