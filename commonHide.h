/**
 * Created by Sol Jennings on 13/3/17.
*/

#ifndef ASS1_COMMONHIDE_H
#define ASS1_COMMONHIDE_H

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

enum execMode {
  multiFiles,
  parallel,
  directory,
  beforeAndAfter
};

typedef struct {
  char *message;
  size_t currentPos;
  size_t length;
} MessageInfo;

void encodeMessageInFile(FILE *file_ptr, char *outputFile, struct ImageInfo *imageInfo, MessageInfo *messageInfo);
void copyHeader(FILE *file_ptr, FILE *outfile_ptr, struct ImageInfo *imageInfo);
void encodeByteToOutput(int byte, FILE *file_ptr, FILE *outfile_ptr, char *outputFile, MessageInfo *messageInfo);

void freeSecretMessageStruct(MessageInfo *messageInfo);
MessageInfo createSecretMessageStruct(char *message);

#endif //ASS1_COMMONHIDE_H

