/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for unhiding a message in an image file
*/


#ifndef ASS1_UNHIDE_H
#define ASS1_UNHIDE_H

#ifndef PATH_MAX
// Maximum length of a linux path
#define PATH_MAX 4096
#endif

void usage();
void mSwitch(int argc, char *argv[]);
void noSwitch(int argc, char *argv[]);

#endif //ASS1_UNHIDE_H
