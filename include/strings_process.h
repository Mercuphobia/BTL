#ifndef STRINGS_PROCESS_H
#define STRINGS_PROCESS_H

// void remove_word(const char *input, const char *word_to_remove, char *output);
//void replace_word(const char *input, const char *word_to_place, const char *replacement, char *output);
//void remove_word_at_index(const char *input, int index, char *output);
//void insert_word_index(const char *input, const char *word_to_insert, int index, char *output);
int count_words(const char *str);
int count_substring(const char *str, char *substr);

char *remove_word(const char *input, const char *word_to_remove);
char *replace_word(const char *input, const char *word_to_place, const char *replacement);
char *remove_word_at_index(const char *input, int index);
char *insert_word_index(const char *input, const char *word_to_insert, int index);

#endif // STRINGS_PROCESS_H