/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Contains the common functionality required to hide an image
*/

#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#define BUFF_SIZE 512

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

/**
 * Enumeration of different hide modes
 * This is so that the encode in message function knows whether it is encoding
 * into one image or multiple
 */
enum HideMode {
  single,
  multiple,
  multipleDir
};

/**
 * Message info type
 *
 * @param message stores the pointer to the message
 * @param currentPos stores the current position where the message has been encoded p to
 * @param length the length of the message in characters
 * @param hideMode the current mode that the messge is being hidden with
 */
typedef struct {
  char *message;
  size_t currentPos;
  size_t length;
  enum HideMode hideMode;
} MessageInfo;

bool encodeMessageInFile(char *inputFile, char *outputFile, MessageInfo *messageInfo);
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, ImageInfo *imageInfo_ptr);
void encodeByteToOutput(int byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile, MessageInfo *messageInfo);
void freeSecretMessageStruct(MessageInfo *messageInfo);
MessageInfo *readFromInput();

#endif //ASS1_COMMONHIDE_H

