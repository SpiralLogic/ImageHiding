CC=gcc
SWITCHES=-Wall
HIDEFILES = hide.c common.c commonHide.c ppmHide.c ppmCommon.c bmpHide.c bmpCommon.c
UNHIDEFILES = unhide.c common.c commonUnhide.c ppmCommon.c ppmUnhide.c bmpUnhide.c bmpCommon.c

all: clean hide unhide

alldebug: clean hidedebug unhidedebug

hide: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) $(SWITCHES) -o hide $(HIDEFILES)

hidedebug: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) $(SWITCHES) -DDEBUG -o hide $(HIDEFILES)

unhide: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) $(SWITCHES) -o unhide $(UNHIDEFILES)

unhidedebug: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) $(SWITCHES) -DDEBUG -o unhide $(UNHIDEFILES)

clean:
	rm -f hide unhide
	rm -rf outputimages
