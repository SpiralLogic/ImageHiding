# standard variables
CC=gcc
CFLAGS=-Wall

# other variables
HIDE_PROGRAM = hide
UNHIDE_PROGRAM = unhide
OUTPUT_DIRECTORY=outputimages
DEBUGGING = debug

HIDEFILES = hide.c common.c commonHide.c ppmHide.c ppmCommon.c bmpHide.c bmpCommon.c
UNHIDEFILES = unhide.c common.c commonUnhide.c ppmCommon.c ppmUnhide.c bmpUnhide.c bmpCommon.c



all: clean $(HIDE_PROGRAM) $(UNHIDE_PROGRAM)

alldebug: clean $(HIDE_PROGRAM)$(DEBUGGING) $(UNHIDE_PROGRAM)$(DEBUGGING)

$(HIDE_PROGRAM): hide.c ppmHide.c common.c ppmCommon.c
	$(CC) $(CFLAGS) -o $(HIDE_PROGRAM) $(HIDEFILES)

$(HIDE_PROGRAM)$(DEBUGGING): hide.c ppmHide.c common.c ppmCommon.c
	$(CC) $(CFLAGS) -DDEBUG -o $(HIDE_PROGRAM) $(HIDEFILES)

$(UNHIDE_PROGRAM): unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) $(CFLAGS) -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

$(UNHIDE_PROGRAM)$(DEBUGGING): unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) $(CFLAGS) -DDEBUG -o $(UNHIDE_PROGRAM) $(UNHIDEFILES)

clean:
	rm -f $(HIDE_PROGRAM) $(UNHIDE_PROGRAM)
	rm -rf $(OUTPUT_DIRECTORY)