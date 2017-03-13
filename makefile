CC=gcc

all: clean hide unhide

hide: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) -o hide hide.c common.c commonHide.c ppmHide.c ppmCommon.c bmpHide.c bmpCommon.c

unhide: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) -o unhide unhide.c common.c commonUnhide.c ppmCommon.c ppmUnhide.c bmpUnhide.c bmpCommon.c

clean:
	rm -f hide unhide outfile.ppm