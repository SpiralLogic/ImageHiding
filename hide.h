/**
 * Created by Sol Jennings on 13/3/17.
 *
 * Main executable for hiding a message in an image file
*/


#ifndef ASS1_HIDE_H_H
#define ASS1_HIDE_H_H

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef PIDS_TO_STORE
#define PIDS_TO_STORE 10
#endif

void noSwitch(int argc, char *argv[]);
void mSwitch(int argc, char *argv[]);
void pSwitch(int argc, char *argv[]);
void sSwitch(int argc, char *argv[]);
void fSwitch(int argc, char *argv[]);
void dSwitch(int argc, char *argv[]);
void usage();

#endif //ASS1_HIDE_H_H
