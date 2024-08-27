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
    LOG(LOG_LVL_WARN, "This is a warning message in line %d\n",__LINE__);
	LOG(LOG_LVL_WARN, "This is a warning message in line %d\n",__LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
	LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
	if (!stop_execution)
	{
		printHello();
		//LOG(LOG_LVL_ERROR, "This is an error message %d\n", __LINE__);
	}

	return 0;
}
