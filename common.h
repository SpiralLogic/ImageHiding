/**
 * Created by Sol Jennings on 13/3/17.
*/

#ifndef ASS1_COMMON_H
#define ASS1_COMMON_H

#include <stdio.h>
#include <stdbool.h>

/**
 * Enum of supported image types
 */
enum ImageType {
  unsupported,
  ppm,
  bmp
};

/**
 * Structure for storing information about an image as read from the header
 * If the header can't be read successfully an error message is stored
 * so that it can be displayed to the user.
 */
struct ImageInfo {
  enum ImageType type;
  char *filename;
  int width;
  int height;
  int depth;
  long pixelMapOffset;
  bool successRead;
  char *errorMesssage;
};

enum ImageType getImageType(FILE *file_ptr);
void errorAndExit(char *error, FILE *file_ptr);
void messageAndExit(char *message, FILE *file_ptr);
void printImageInfo(struct ImageInfo *imageInfo);

#ifdef DEBUG
void printByteBits(int byte);
#endif

#endif //ASS1_COMMON_H
