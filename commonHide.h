//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#include <stdbool.h>
#include "common.h"

void encodeImage(FILE *file_ptr, struct ImageInfo *imageInfo, char *outputFile, char *message);
bool doesMessageFit(struct ImageInfo *imageInfo, char *message);
void copyHeader(FILE *file_ptr, FILE *outfile, struct ImageInfo *imageInfo);

#endif //ASS1_COMMONHIDE_H

