#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parsers_option.h"
#include "hello.h"
#include "strings_process.h"
#include "log.h"
#include "file_process.h"
#include "cJSON.h"

void function1()
{
	LOG(LOG_LVL_WARN, "This is a warning from function1\n", __LINE__);
	LOG(LOG_LVL_DEBUG, "Debugging in function1, line %d\n", __LINE__);
}


void convert_to_json(const char *filename)
{
	FILE *file = open_file(filename, "r");
	if (!file)
	{
		printf("Failed open file.\n");
		return;
	}

	cJSON *root = cJSON_CreateObject();	  // Tạo đối tượng JSON gốc
	cJSON *ap_list = cJSON_CreateArray(); // Tạo mảng cho các AP

	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		char ssid[64], bssid[32];
        if (sscanf(line,"%*d %*d %63s %31s", ssid, bssid) == 2)
        {
            cJSON *ap = cJSON_CreateObject();
            cJSON_AddStringToObject(ap, "SSID", ssid);
            cJSON_AddStringToObject(ap, "BSSID", bssid);
            cJSON_AddItemToArray(ap_list, ap);
        }
	}

	cJSON_AddItemToObject(root, "AP_List", ap_list);

	char *json_string = cJSON_Print(root);
	printf("JSON output:\n%s\n", json_string);

	// Ghi JSON ra file
	FILE *output_file = open_file("./data/list.json", "w");
	if (output_file != NULL)
	{
		fprintf(output_file,"%s", json_string);
		fclose(output_file);
	}

	cJSON_Delete(root);
	free(json_string);
	fclose(file);
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
	printf("%s\n", "Please wait a moment!");
	sleep(2);
	system("/userfs/bin/iwpriv rai0 get_site_survey > /tmp/test_code/data/neigbor_ap");
	// system("cat /tmp/test_code/data/neigbor_ap");

	convert_to_json("./data/neigbor_ap");
	return 0;
}
