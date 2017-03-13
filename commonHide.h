//
// Created by Sol Jennings on 13/3/17.
//

#include <stdbool.h>
#include "common.h"

#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#endif //ASS1_COMMONHIDE_H

void encodeImage(FILE *file, struct ImageInfo imageInfo, char *outputFile, char *message);
bool doesMessageFit(struct ImageInfo info, char *message);
void copyHeader(FILE *file, FILE *outfile, struct ImageInfo imageInfo);

