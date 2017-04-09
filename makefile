#################################
# Standard compiler variables
#################################
CC=gcc
CFLAGS=-Wall

#################################
# Compiler output names
#################################
HIDE_PROGRAM = hide
UNHIDE_PROGRAM = unhide
OUTPUT_DIRECTORY = outputimages
DEBUGGING = debug

#################################
# file lists
#################################
HIDEFILES = hide.c common.c commonHide.c ppmCommon.c bmpCommon.c
UNHIDEFILES = unhide.c common.c commonUnhide.c ppmCommon.c bmpCommon.c

#################################
# Each of the make builds
#################################
all: clean $(HIDE_PROGRAM) $(UNHIDE_PROGRAM)

ppmCommon.o: ppmCommon.c
	$(CC) $(CFLAGS) -c ppmCommon.c

bmpCommon.o: bmpCommon.c
	$(CC) $(CFLAGS) -c bmpCommon.c

common.o: common.c
	$(CC) $(CFLAGS) -c common.c

$(HIDE_PROGRAM): ppmCommon.o bmpCommon.o common.o
	$(CC) $(CFLAGS) -o $(HIDE_PROGRAM) $(HIDEFILES)

$(UNHIDE_PROGRAM): ppmCommon.o bmpCommon.o common.o
	$(CC) $(CFLAGS) -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

#################################
# debugging builds
#################################
alldebug: clean $(HIDE_PROGRAM)$(DEBUGGING) $(UNHIDE_PROGRAM)$(DEBUGGING)

$(HIDE_PROGRAM)$(DEBUGGING):
	$(CC) $(CFLAGS) -DDEBUG -g -o $(HIDE_PROGRAM) $(HIDEFILES)

$(UNHIDE_PROGRAM)$(DEBUGGING):
	$(CC) $(CFLAGS) -DDEBUG -g -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

#################################
# clean
#################################
clean:
	rm -f $(HIDE_PROGRAM) $(UNHIDE_PROGRAM)
	rm -rf $(OUTPUT_DIRECTORY)
