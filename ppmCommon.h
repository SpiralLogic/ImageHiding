//
// Created by Sol Jennings on 13/3/17.
//
#ifndef ASS1_PPMCOMMON_H
#define ASS1_PPMCOMMON_H

void moveFileToNextLine(FILE *file_ptr);
int scanDimension(FILE *file_ptr);
struct ImageInfo getPpmImageInfo(FILE *file_ptr);

#endif //ASS1_PPMCOMMON_H


