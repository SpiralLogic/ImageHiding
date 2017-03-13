//
// Created by Sol Jennings on 13/3/17.
//

#include <stdio.h>
#include <stdbool.h>
#include "common.h"

#ifndef ASS1_BMPHIDE_H
#define ASS1_BMPHIDE_H
#endif //ASS1_BMPHIDE_H

void hideInBmp(FILE *file, char *message);
void encodePpmImage(FILE *file, struct ImageInfo imageInfo, char *message);
void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo);
bool doesMessageFit(struct ImageInfo info, char *message);
