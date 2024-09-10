#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *remove_word(const char *input, const char *word_to_remove) {
    const char *start = input;
    int output_size = strlen(input) + 1;
    char *output = malloc(output_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
    }
    output[0] = '\0';

    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (strncmp(start, word_to_remove, end - start) == 0 && (end - start) == strlen(word_to_remove)) {
            start = end;
            while (isspace(*start)) start++;
            continue;
        }

        output_size += (end - start + 2);
        char *new_output = realloc(output, output_size);
        if (new_output == NULL) {
            perror("Failed to realloc memory");
            free(output);
        }
        output = new_output;

        strncat(output, start, end - start);
        strcat(output, " ");
        start = end;
        while (isspace(*start)) start++;
    }

    int output_len = strlen(output);
    if (output_len > 0 && output[output_len - 1] == ' ') {
        output[output_len - 1] = '\0';
    }

    return output;
}

char *replace_word(const char *input, const char *word_to_place, const char *replacement) {
    const char *start = input;
    int output_size = strlen(input) + 1;
    char *output = malloc(output_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
    }
    output[0] = '\0';
    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (strncmp(start, word_to_place, end - start) == 0 && (end - start == strlen(word_to_place))) {
            strcat(output, replacement);
            strcat(output, " ");
            start = end;
            while (isspace(*start)) start++;
            continue;
        }

        output_size += (end - start + 2);
        char *new_output = realloc(output, output_size);
        if (new_output == NULL) {
            perror("Failed to realloc memory");
            free(output);
        }
        output = new_output;

        strncat(output, start, end - start);
        strcat(output, " ");
        start = end;
        while (isspace(*start)) start++;
    }
    return output;
}

char *remove_word_at_index(const char *input, int index) {
    const char *start = input;
    int count = 0;
    int output_size = strlen(input) + 1;
    char *output = malloc(output_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
    }
    output[0] = '\0';
    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (count == index) {
            start = end;
            while (isspace(*start)) start++;
            count++;
            continue;
        }
        
        output_size += (end - start + 2);
        char *new_output = realloc(output, output_size);
        if (new_output == NULL) {
            perror("Failed to realloc memory");
            free(output);
        }
        output = new_output;

        strncat(output, start, end - start);
        strcat(output, " ");
        start = end;
        while (isspace(*start)) start++;
        count++;
    }
    if (count == index) {
        strcat(output, " ");
    }
    int output_len = strlen(output);
    if (output_len > 0 && output[output_len - 1] == ' ') {
        output[output_len - 1] = '\0';
    }
    return output;
}

char *insert_word_index(const char *input, const char *word_to_insert, int index) {
    const char *start = input;
    int count = 0;
    int output_size = strlen(input) + strlen(word_to_insert) + 2;
    char *output = malloc(output_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    output[0] = '\0';

    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (count == index) {
            strcat(output, word_to_insert);
            strcat(output, " ");
        }

        int segment_length = end - start;
        output_size += segment_length + 2;
        char *new_output = realloc(output, output_size);
        if (new_output == NULL) {
            perror("Failed to realloc memory");
            free(output);
            return NULL;
        }
        output = new_output;

        strncat(output, start, segment_length);
        strcat(output, " ");
        start = end;
        while (isspace(*start)) start++;
        count++;
    }

    if (count == index) {
        strcat(output, word_to_insert);
        strcat(output, " ");
    }

    int output_len = strlen(output);
    if (output_len > 0 && output[output_len - 1] == ' ') {
        output[output_len - 1] = '\0';
    }

    return output;
}

int count_words(const char *str) {
    int count = 0;
    int in_word = 0;
    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

int count_substring(const char *str, const char *substr) {
    int count = 0;
    const char *temp = str;
    while ((temp = strstr(temp, substr)) != NULL) {
        count++;
        temp++;
    }

    return count;
}

void trim_space_end(char *str){
    int len = strlen(str);
    while(len > 0 && isspace((unsigned char)str[len-1])){
        str[len-1] = '\0';
        len--;
    }
}
void trim_space_start(char *str){
    int index = 0;
    int len = strlen(str);
    while(index!= '\0' && isspace((unsigned char)str[index])){
        index++;
    }
    if(index >0){
        memmove(str, str + index, len - index + 1);
    }
}

char *trim_whitespace(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0)  
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
    return str;
}