CC=gcc
HIDEFILES = hide.c common.c commonHide.c ppmHide.c ppmCommon.c bmpHide.c bmpCommon.c
all: clean hide unhide

alldebug: clean hide unhide

hide: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) -o hide $(HIDEFILES)

hidedebug: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) -o -dDEBUG hide $(HIDEFILES)

unhide: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) -o unhide unhide.c common.c commonUnhide.c ppmCommon.c ppmUnhide.c bmpUnhide.c bmpCommon.c

unhidedebug: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) -o -dDEBUG unhide unhide.c common.c commonUnhide.c ppmCommon.c ppmUnhide.c bmpUnhide.c bmpCommon.c

clean:
	rm -f hide unhide outfile.ppm