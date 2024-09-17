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
    }
    else
    {
        scan_wifi_when_start();
        convert_to_json(INPUT_PATH,OUTPUT_PATH);
    }
    return 0;
}
