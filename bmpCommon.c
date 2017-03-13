//
// Created by Sol Jennings on 13/3/17.
//

#include "common.h"
#include "bmpCommon.h"


struct ImageInfo getBmpImageInfo(FILE *file) {
    struct ImageInfo imageInfo = {.height = 0, .width =0, .depth = 0, .imageMapPosition = 0};

    fseek(file, 10, SEEK_SET);
    fread(&imageInfo.imageMapPosition, 4, 1, file);

    fseek(file, 18, SEEK_SET);
    fread(&imageInfo.width, 4, 1, file);

    fseek(file, 22, SEEK_SET);
    fread(&imageInfo.height, 4, 1, file);

    fseek(file, 28, SEEK_SET);
    fread(&imageInfo.depth, 2, 1, file);



    return imageInfo;
}
