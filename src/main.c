#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

	system("/userfs/bin/iwpriv rai0 set SiteSurvey=1");
	printf("%s\n","Please wait a moment!");
	sleep(2);
	system("/userfs/bin/iwpriv rai0 get_site_survey > /tmp/test_code/data/neigbor_ap");
	//system("cat /tmp/test_code/data/neigbor_ap");
	return 0;
}
