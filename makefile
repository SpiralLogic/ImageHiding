CC=gcc

all: clean hide unhide

hide: hide.c ppmHide.c common.c ppmCommon.c
	$(CC) -o hide hide.c common.c ppmHide.c ppmCommon.c bmpHide.c bmpCommon.c

writeMsg: unhide.c ppmUnhide.c common.c ppmCommon.c
	$(CC) -o unhide unhide.c ppmUnhide.c common.c ppmCommon.c

clean:
	rm -f hide unhide outfile.ppm