/**
 * Created by Sol Jennings on 13/3/17.
*/

#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#define BUFF_SIZE 1024

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

enum HideMode {
  single,
  multiple
};

typedef struct {
  char *message;
  size_t currentPos;
  size_t length;
  enum HideMode hideMode;
} MessageInfo;

void encodeMessageInFile(char *inputFile, char *outputFile, MessageInfo *messageInfo);
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo_ptr);
void encodeByteToOutput(int byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile, MessageInfo *messageInfo);
char* readFromInput();
void freeSecretMessageStruct(MessageInfo *messageInfo);
MessageInfo createSecretMessageStruct(char *message);

#endif //ASS1_COMMONHIDE_H

