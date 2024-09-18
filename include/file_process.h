#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

FILE* open_file(const char* filename,const char* mode);

char *read_file(FILE* file);

void write_to_file(FILE* file, const char* content);

void insert_word_at_position(const char* filename,const char* word,long position);

int position_mac(const char *line);

int find_end_position_of_second_number(const char *line);

void printf_json_in_file(const char *output_file,const char *json_string);

void convert_to_json(const char *input_file, const char *output_file);

void scan_and_write_wifi_5G();

void scan_and_write_wifi_2G();

void scan_and_write_all();

void scan_wifi_when_start();

#endif // FILE_PROCESS_H