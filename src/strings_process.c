#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_word(const char *input, const char *word_to_move, char *output) {
    const char *start = input;
    char temp[1024];
    temp[0] = '\0';
    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (strncmp(start, word_to_move, end - start) == 0 && (end - start == strlen(word_to_move))) {
            start = end;
            while (isspace(*start)) start++;
            continue;
        }
        strncat(temp, start, end - start);
        strcat(temp, " ");
        start = end;
        while (isspace(*start)) start++;
    }
    strcpy(output, temp);
}

void replace_word(const char *input, const char *word_to_place, const char *replacement, char *output) {
    const char *start = input;
    char temp[1024];
    temp[0] = '\0';
    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (strncmp(start, word_to_place, end - start) == 0 && (end - start == strlen(word_to_place))) {
            strcat(temp, replacement);
            strcat(temp, " ");
            start = end;
            while (isspace(*start)) start++;
            continue;
        }
        strncat(temp, start, end - start);
        strcat(temp, " ");
        start = end;
        while (isspace(*start)) start++;
    }
    strcpy(output, temp);
}

void remove_word_at_index(const char *input, int index, char *output) {
    const char *start = input;
    int count = 0;
    char temp[1024];
    temp[0] = '\0';
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
        strncat(temp, start, end - start);
        strcat(temp, " ");
        start = end;
        while (isspace(*start)) start++;
        count++;
    }
    if (count == index) {
        strcat(temp, " ");
    }
    strcpy(output, temp);
}

void insert_word_index(const char *input, const char *word_to_insert, int index, char *output) {
    const char *start = input;
    int count = 0;
    char temp[1024];
    temp[0] = '\0';
    while (*start) {
        const char *end = start;
        while (*end && !isspace(*end)) {
            end++;
        }
        if (count == index) {
            strcat(temp, word_to_insert);
            strcat(temp, " ");
        }
        strncat(temp, start, end - start);
        strcat(temp, " ");
        start = end;
        while (isspace(*start)) start++;
        count++;
    }
    if (count == index) {
        strcat(temp, word_to_insert);
        strcat(temp, " ");
    }
    strcpy(output, temp);
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

int count_char(const char *str, char ch) {
    int count = 0;
    while (*str) {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}
