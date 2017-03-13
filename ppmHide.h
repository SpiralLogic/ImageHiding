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
void encodeImage(FILE *file, struct ImageInfo imageInfo, char *message);
void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo);
bool doesMessageFit(struct ImageInfo info, char *message);
