//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#include <stdbool.h>
#include "common.h"

void encodeImage(FILE *file, struct ImageInfo imageInfo, char *outputFile, char *message);
bool doesMessageFit(struct ImageInfo info, char *message);
void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo);

#endif //ASS1_COMMONHIDE_H

