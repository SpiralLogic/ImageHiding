//
// Created by Sol Jennings on 14/4/17.
//
#include <stdio.h>

int main(int argc, char *argv[]) {
    size_t test = 225600;
    char sizetarray[sizeof(size_t)];
    size_t result = 0;

    printf("%zu\n", test);


    for (int i=sizeof(size_t) - 1; i >= 0; i--) {
        char a = (test >> (i * 8)) & 0xff;
        sizetarray[i] = a;
        printf("%x\n", sizetarray[i]);
    }

    for (int i=0; i < sizeof(size_t); i++) {
        printf("%x\n", sizetarray[i]);
        result |= (sizetarray[i] << (i * 8));
    }
    printf("%zu\n", result);
    return 0;
}