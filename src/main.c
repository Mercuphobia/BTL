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

void convert_to_json(const char *filename, int line_number)
{
    FILE *file = open_file(filename, "r");
    if (!file)
    {
        perror("Failed to open file\n");
        return;
    }

    char line[256];
    int current_line = 0;

    while (fgets(line, sizeof(line), file))
    {
        current_line++;
        if (current_line == line_number)
        {
            break;
        }
    }

    if (current_line != line_number)
    {
        printf("Line %d not found in file\n", line_number);
        fclose(file);
        return;
    }

    line[strcspn(line, "\n")] = 0;
    cJSON *root = cJSON_CreateObject();
    cJSON *ap_list = cJSON_CreateArray();
    while (fgets(line, sizeof(line), file))
    {

        char index[4] = {0}, channel[4] = {0}, ssid[33] = {0}, bssid[20] = {0}, security[23] = {0}, signal[9] = {0};
        char w_mode[8] = {0}, extch[7] = {0}, nt[3] = {0}, wps[3] = {0}, dpid[5] = {0}, bcnrept[9] = {0};

        strncpy(index, line + 0, 3);
        strncpy(channel, line + 4, 3);
        strncpy(ssid, line + 8, 32);
        strncpy(bssid, line + 41, 17);
        // strncpy(security, line + 41, 17);
        //  strncpy(signal, line + 49, 8);
        //  strncpy(w_mode, line + 58, 7);
        //  strncpy(extch, line + 66, 6);
        //  strncpy(nt, line + 73, 2);
        //  strncpy(wps, line + 76, 2);
        //  strncpy(dpid, line + 79, 4);
        //  strncpy(bcnrept, line + 83, 8);

        int word_count = count_words(ssid);
        trim_whitespace(bssid);
        trim_whitespace(ssid);
        int num_index = atoi(index);
        if (word_count > 0)
        {
            cJSON *ap = cJSON_CreateObject();
            // cJSON_AddNumberToObject(ap, "Index", num_index);
            // cJSON_AddStringToObject(ap, "Channel", channel);
            cJSON_AddStringToObject(ap, "SSID", ssid);
            cJSON_AddStringToObject(ap, "BSSID", bssid);
            cJSON_AddItemToArray(ap_list, ap);
        }
    }
    // int ap_count = cJSON_GetArraySize(ap_list);
    // printf("number ap: %d\n", ap_count);
    // for (int i = 0; i < ap_count; i++)
    // {
    //     cJSON *ap = cJSON_GetArrayItem(ap_list, i);
    //     if (cJSON_IsObject(ap))
    //     {
    //         cJSON *index = cJSON_GetObjectItem(ap, "Index");
    //         cJSON *channel = cJSON_GetObjectItem(ap, "Channel");
    //         cJSON *ssid = cJSON_GetObjectItem(ap, "SSID");
    //         cJSON *bssid = cJSON_GetObjectItem(ap, "BSSID");

    //         printf("AP %d:\n", i + 1);
    //         // printf("  Index: %d\n", index ? index->valueint : -1);
    //         // printf("  Channel: %s\n", channel ? channel->valuestring : "N/A");
    //         printf("  SSID: %s\n", ssid ? ssid->valuestring : "N/A");
    //         printf("  BSSID: %s\n", bssid ? bssid->valuestring : "N/A");
    //     }
    // }
    cJSON_AddItemToObject(root, "AP_List", ap_list);
    char *json_string = cJSON_Print(root);
    printf("JSON output:\n%s\n", json_string);

    FILE *output_file = open_file("./data/list.json", "w");
    if (output_file != NULL)
    {
        fprintf(output_file, "%s", json_string);
    }
    cJSON_Delete(root);
    free(json_string);
    fclose(file);
}

int main(int argc, char *argv[])
{   
    if (argc > 1)
    {
        parsers_option(argc, argv);
        LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
        // LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 100);
        // LOG(LOG_LVL_ERROR, "This is an error message with value: %d\n", 101);
        // LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
        // LOG(LOG_LVL_WARN, "This is a warning message in line %d\n", __LINE__);
        // LOG(LOG_LVL_DEBUG, "%s, %d: test1\n", __func__, __LINE__);
    }
    else
    {   
        
        LOG(LOG_LVL_DEBUG, "%s, %d: test2\n", __func__, __LINE__);

        // system("/userfs/bin/iwpriv rai0 set SiteSurvey=1");
        printf("%s\n", "Please wait a moment!");
        sleep(2);
        // system("/userfs/bin/iwpriv rai0 get_site_survey > /tmp/test_code/data/neigbor_ap");
        // system("cat /tmp/test_code/data/neigbor_ap");
        convert_to_json("./data/neigbor_ap", 3);
        void print_help();
        return 0;
   }
}
