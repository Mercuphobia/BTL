#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

FILE* open_file(const char* filename,const char* mode);

char *read_file(FILE* file);

void write_to_file(FILE* file, const char* content);

void insert_word_at_position(const char* filename,const char* word,long position);

#endif // FILE_PROCESS_H