#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file(const char *file_name, const char *mode){
    FILE *file = fopen(file_name,mode);
    if(!file){
        perror("Open file false");
    }
    return file;
}

