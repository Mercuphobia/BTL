#include <stdio.h>
#include <stdlib.h>
#include "parsers_option.h"
#include "hello.h"
#include "strings_process.h"
#include "log.h"

int main(int argc, char *argv[])
{
	parsers_option(argc, argv);
	LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
	LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 101);
	LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
	LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test2\n", __func__, __LINE__);
	if (!stop_execution)
	{
		printHello();
		const char *input = "hoc vien cong nghe buu chinh vien thong khoa 2024 la d24 nam 2024 co khoa moi 2024 cx la nam lam lai nha xe";
    	const char *word_to_remove = "2024";
    	char *result = remove_word(input, word_to_remove);
    	printf("Modified: %s\n", result);
		char *result2 = remove_word_at_index(input,3);
		printf("Modified2: %s\n", result2);
		char *result3 = insert_word_index(input,"trung duc le ",3);
		printf("Modified3: %s\n", result3);
		printf("%d\n",count_substring(result3,"2024"));
    	free(result2);
		free(result3);
	}

	return 0;
}
