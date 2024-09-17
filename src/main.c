#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parsers_option.h"
#include "hello.h"
#include "strings_process.h"
#include "log.h"
#include "file_process.h"
#include "cJSON.h"
#include <string.h>

#define OUTPUT_PATH "./data/list.json"
#define INPUT_PATH "./data/neigbor_ap"




int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        parsers_option(argc, argv);
        LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
        // LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
    }
    else
    {

        LOG(LOG_LVL_DEBUG, "%s, %d: test2\n", __func__, __LINE__);
        // system("/userfs/bin/iwpriv rai0 set SiteSurvey=1");
        // printf("%s\n", "Please wait a moment!");
        // sleep(2);
        // system("/userfs/bin/iwpriv rai0 get_site_survey > /tmp/test_code/data/neigbor_ap");
        // system("cat /tmp/test_code/data/neigbor_ap");
        scan_wifi_start();
        convert_to_json(INPUT_PATH,OUTPUT_PATH);
        return 0;
    }
}
