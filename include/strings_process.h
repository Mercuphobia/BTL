#ifndef STRINGS_PROCESS_H
#define STRINGS_PROCESS_H

int count_words(const char *str);
int count_substring(const char *str, char *substr);
void trim_space(char *str);
char *remove_word(const char *input, const char *word_to_remove);
char *replace_word(const char *input, const char *word_to_place, const char *replacement);
char *remove_word_at_index(const char *input, int index);
char *insert_word_index(const char *input, const char *word_to_insert, int index);

#endif // STRINGS_PROCESS_H