/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains the common functionality required for PPM file
*/

#ifndef ASS1_PPMCOMMON_H
#define ASS1_PPMCOMMON_H

#include "common.h"

// Supported PPM colour depth
#define PPM_COLOR_DEPTH 255

bool moveFileToNextLine(FILE *file_ptr);
int scanDimension(FILE *file_ptr);
ImageInfo getPpmImageInfo(FILE *file_ptr);
ImageInfo verifyAndGetPpmInfo(FILE *file_ptr);

#endif //ASS1_PPMCOMMON_H


