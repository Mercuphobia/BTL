#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

FILE *open_file(const char *file_name, const char *mode){
    FILE *file = fopen(file_name,mode);
    if(!file){
        perror("Open file false");
    }
    return file;
}

char *read_file(FILE* file){
    if(file == NULL){
        return NULL;
    }

    fseek(file,0,SEEK_END);
    long long filesize = ftell(file);
    rewind(file);

    char* content = (char*)malloc(sizeof(char)* (filesize+1));
    if(content == NULL){
        perror("Failed to allocate memory");
        return NULL;
    }
    fread(content,sizeof(char),filesize,file);
    content[filesize] = '\0';
    return content;
}

void write_to_file(FILE* file, const char* content){
    if(file == NULL){
        return;
    }
    fprintf(file,"%s",content);
    
}

void insert_word_at_position(const char* filename,const char* word,long position){
    FILE *file = open_file(filename,"r+");
    if(file == NULL){
        return;
    }

    fseek(file,0,SEEK_END);
    long long filesize = ftell(file);
    rewind(file);

    char *content = (char *)malloc(filesize+1);
    if(content == NULL){
        perror("Failed to allocte memory");
        fclose(file);
        return;
    }

    fread(content,sizeof(char),filesize,file);
    content[filesize] = '\0';

    long new_size = filesize + strlen(word);
    char *new_content = (char *)malloc(new_size + 1);
    if(new_content == NULL){
        perror("Failed to allocate memory");
        free(content);
        fclose(file);
        return;
    }

    strncpy(new_content,content,position);
    strcpy(new_content + position, word);
    strcpy(new_content + position + strlen(word),content + position);

    new_content[new_size] = '\0';

    freopen(filename,"w",file);
    fwrite(new_content,sizeof(char),new_size,file);

    free(content);
    free(new_content);
    fclose(file);

}
