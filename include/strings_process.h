#ifndef STRINGS_PROCESS_H
#define STRINGS_PROCESS_H

void remove_word(const char *input, const char *word_to_remove, char *output);
void replace_word(const char *input, const char *word_to_place, const char *replacement, char *output);
void remove_word_at_index(const char *input, int index, char *output);
void insert_word_index(const char *input, const char *word_to_insert, int index, char *output);
int count_words(const char *str);
int count_char(const char *str, char ch);

#endif // STRINGS_PROCESS_H