//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_BMPHIDE_H
#define ASS1_BMPHIDE_H

#define BMP_COLOR_DEPTH 24

#include <stdio.h>
#include "common.h"

struct ImageInfo verifyAndGetBmpInfo(FILE *file_ptr);

#endif //ASS1_BMPHIDE_H
