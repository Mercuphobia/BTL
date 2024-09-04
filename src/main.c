#include <stdio.h>
#include <stdlib.h>
#include "parsers_option.h"
#include "hello.h"
#include "strings_process.h"
#include "log.h"
#include "file_process.h"

void function1() {
    LOG(LOG_LVL_WARN, "This is a warning from function1\n",__LINE__);
    LOG(LOG_LVL_DEBUG, "Debugging in function1, line %d\n", __LINE__);
}

int main(int argc, char *argv[])
{
	parsers_option(argc, argv);
	LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
	LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 101);
	LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
	LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test2\n", __func__, __LINE__);
	function1();


	if (!stop_execution)
	{
		LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
		// printHello();
		// const char *input = "hoc vien cong nghe buu chinh vien thong khoa 2024 la d24 nam 2024 co khoa moi 2024 cx la nam lam lai nha xe";
    	// const char *word_to_remove = "2024";
    	// char *result = remove_word(input, word_to_remove);
    	// printf("Modified: %s\n", result);
		// char *result2 = remove_word_at_index(input,3);
		// printf("Modified2: %s\n", result2);
		// char *result3 = insert_word_index(input,"trung duc le ",3);
		// printf("Modified3: %s\n", result3);
		// printf("%d\n",count_substring(result3,"2024"));
    	// free(result2);
		// free(result3);


		const char* filename = "test.json";
		FILE* file = open_file(filename, "r+");
    	char* content = read_file(file);
		fclose(file);
		const char *word_to_remove = "glossary";
		char *result2 = remove_word_at_index(content,1);
		FILE* write_file = open_file("test.txt","w");

		write_to_file(write_file,result2);
		fclose(write_file);
		// const char *filename1 = "test.txt";
		// FILE *file1 = open_file(filename1,"r+");
		// char *readfile1 = read_file(file1);
		// printf("%d\n",count_words(readfile1));

		//insert_word_at_position("test.txt","trung-test",1);

		//printf("%s\n",insert_word_index(content,"trung duc le ",3));
		// FILE *file_write = open_file("test.txt", "w");
		// write_to_file(file_write,new_content);
		// fclose(file);

	}

	return 0;
}
