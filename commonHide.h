/*
 * Created by Sol Jennings on 13/3/17.
*/

#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

void readAndEncodeMessage(FILE *file_ptr, struct ImageInfo *imageInfo, char *outputFile);
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo);
void encodeByteToOutput(int *byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile);

#endif //ASS1_COMMONHIDE_H

