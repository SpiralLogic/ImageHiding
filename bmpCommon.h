//
// Created by Sol Jennings on 13/3/17.
//

#ifndef ASS1_BMPCOMMON_H
#define ASS1_BMPCOMMON_H

// The bit depth BMP encoding supports
#define BMP_IMAGE_BITS 24

#include <stdio.h>

struct ImageInfo getBmpImageInfo(FILE *file_ptr);
struct ImageInfo verifyAndGetBmpInfo(FILE *file_ptr);

#endif //ASS1_BMPCOMMON_H
