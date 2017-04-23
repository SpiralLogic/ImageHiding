#################################
# Standard compiler variables
#################################
CC=gcc
CFLAGS=-Wall -g
SDLCFLAGS=`sdl2-config --cflags`
SDLLIBS=`sdl2-config --libs`

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
HIDEFILES = hide.c common.o commonHide.o compareImages.o ppmCommon.o bmpCommon.o
UNHIDEFILES = unhide.c common.o commonUnhide.o ppmCommon.o bmpCommon.o

#################################
# Each of the make builds
#################################
all: $(HIDE_PROGRAM) $(UNHIDE_PROGRAM)

ppmCommon.o: ppmCommon.c
	$(CC) $(CFLAGS) -c ppmCommon.c

bmpCommon.o: bmpCommon.c
	$(CC) $(CFLAGS) -c bmpCommon.c

common.o: common.c
	$(CC) $(CFLAGS) -c common.c

commonHide.o: commonHide.c
	$(CC) $(CFLAGS) -c commonHide.c

commonUnhide.o: commonUnhide.c
	$(CC) $(CFLAGS) $(SDLCFLAGS) -c commonUnhide.c $(SDLLIBS)

compareImages.o: compareImages.c
	$(CC) $(CFLAGS) $(SDLCFLAGS) -c compareImages.c $(SDLLIBS)

$(HIDE_PROGRAM): hide.c ppmCommon.o bmpCommon.o common.o commonHide.o compareImages.o
	$(CC) $(CFLAGS) $(SDLCFLAGS) -o $(HIDE_PROGRAM) $(HIDEFILES) $(SDLLIBS)

$(UNHIDE_PROGRAM): unhide.c ppmCommon.o bmpCommon.o common.o commonUnhide.o
	$(CC) $(CFLAGS) -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

#################################
# debugging builds
#################################
alldebug: $(HIDE_PROGRAM)$(DEBUGGING) $(UNHIDE_PROGRAM)$(DEBUGGING)

$(HIDE_PROGRAM)$(DEBUGGING): $(HIDEFILES)
	$(CC) $(CFLAGS) $(SDLCFLAGS) -DDEBUG -g -o $(HIDE_PROGRAM) $(HIDEFILES) $(SDLLIBS)

$(UNHIDE_PROGRAM)$(DEBUGGING): $(UNHIDEFILES)
	$(CC) $(CFLAGS) -DDEBUG -g -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

#################################
# clean
#################################
clean:
	rm -f $(HIDE_PROGRAM) $(UNHIDE_PROGRAM) *.o
	rm -rf $(OUTPUT_DIRECTORY)
