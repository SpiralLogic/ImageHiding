//
// Created by Sol Jennings on 13/3/17.
//

#include <stdio.h>
#include <stdbool.h>
#include "common.h"

#ifndef ASS1_PPMHIDE_H
#define ASS1_PPMHIDE_H

#endif //ASS1_PPMHIDE_H

void hideInPpm(FILE *file, char *message);
void encodePpmImage(FILE *file, struct ImageInfo imageInfo, char *message);
bool doesMessageFit(struct ImageInfo info, char *message);
