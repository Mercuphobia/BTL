#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "log.h"
#include "cJSON.h"
#include "strings_process.h"


#define MAC_ADDRESS_FORMAT "%x:%x:%x:%x:%x:%x"
#define WAITING_TIME_SCAN 2
#define SITE_SURVEY_2G "/userfs/bin/iwpriv ra0 set SiteSurvey=1"
#define SITE_SURVEY_5G "/userfs/bin/iwpriv rai0 set SiteSurvey=1"
#define WRITE_2G_TO_FILE "/userfs/bin/iwpriv ra0 get_site_survey > /tmp/test_code/data/neigbor_ap"
#define WRITE_5G_TO_FILE "/userfs/bin/iwpriv rai0 get_site_survey > /tmp/test_code/data/neigbor_ap"
#define INSERT_2G_TO_FILE "/userfs/bin/iwpriv ra0 get_site_survey >> /tmp/test_code/data/neigbor_ap"
#define INSERT_5G_TO_FILE "/userfs/bin/iwpriv rai0 get_site_survey >> /tmp/test_code/data/neigbor_ap"

unsigned int mac[6];
char line[256];

int is_mac_address(const char *string) {
    return sscanf(string, MAC_ADDRESS_FORMAT, &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6;
}


FILE *open_file(const char *file_name, const char *mode){
    FILE *file = fopen(file_name,mode);
    if(!file){
        perror("Open file false");
    }
    return file;
}

char *read_file(FILE* file){
    if(file == NULL){
        return NULL;
    }

    fseek(file,0,SEEK_END);
    long long filesize = ftell(file);
    rewind(file);

    char* content = (char*)malloc(sizeof(char)* (filesize+1));
    if(content == NULL){
        perror("Failed to allocate memory");
        return NULL;
    }
    fread(content,sizeof(char),filesize,file);
    content[filesize] = '\0';
    return content;
}

void write_to_file(FILE* file, const char* content){
    if(file == NULL){
        return;
    }
    fprintf(file,"%s",content);
    
}

void insert_word_at_position(const char* filename,const char* word,long position){
    FILE *file = open_file(filename,"r+");
    if(file == NULL){
        return;
    }

    fseek(file,0,SEEK_END);
    long long filesize = ftell(file);
    rewind(file);

    char *content = (char *)malloc(filesize+1);
    if(content == NULL){
        perror("Failed to allocte memory");
        fclose(file);
        return;
    }

    fread(content,sizeof(char),filesize,file);
    content[filesize] = '\0';

    long new_size = filesize + strlen(word);
    char *new_content = (char *)malloc(new_size + 1);
    if(new_content == NULL){
        perror("Failed to allocate memory");
        free(content);
        fclose(file);
        return;
    }

    strncpy(new_content,content,position);
    strcpy(new_content + position, word);
    strcpy(new_content + position + strlen(word),content + position);

    new_content[new_size] = '\0';

    freopen(filename,"w",file);
    fwrite(new_content,sizeof(char),new_size,file);

    free(content);
    free(new_content);
    fclose(file);

}

int position_mac(const char *line)
{
   char *ptr = (char *)line;
   int mac_len = 17;
   while ((ptr = strchr(ptr, ':')) != NULL) {
        if (ptr > line + mac_len - 1 && is_mac_address(ptr - mac_len + 1)) {
            break;
        }
        ptr++;
    }
    return ptr - line - mac_len + 1;
}

int find_end_position_of_second_number(const char *line) {
    int num1, num2;
    const char *ptr = line;
    
    if (sscanf(ptr, "%d %d", &num1, &num2) == 2) {
        while (*ptr && !isspace(*ptr)) {
            ptr++;
        }
        while (*ptr && isspace(*ptr)) {
            ptr++;
        }
        while (*ptr && !isspace(*ptr)) {
            ptr++;
        }
        while (*ptr && !isspace(*ptr)) {
            ptr++;
        }
    }
    return ptr -line;
}

void printf_json_in_file(const char *output_file,const char *json_string){
    FILE *output = open_file(output_file,"w");
    if(output != NULL){
        fprintf(output,"%s\n",json_string);
        fclose(output);
    }
    else{
        printf("Failed to open file.\n");
    }
}

void convert_to_json(const char *input_file, const char *output_file) {
    FILE *file = open_file(input_file, "r");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }
    cJSON *root = cJSON_CreateObject();
    cJSON *ap_list = cJSON_CreateArray();

    while (fgets(line, sizeof(line), file)) {
        int index, channel;
        char ssid[256] = "";
        if (sscanf(line, "%d %d", &index, &channel) == 2) {
            char *ptr = line;
            int end_number_position = find_end_position_of_second_number(line) + 2;
            int mac_position = position_mac(line);
            
            if (mac_position != -1) {
                strncpy(ssid, line + end_number_position, mac_position - end_number_position);
                ssid[mac_position - end_number_position] = '\0';

                if (sscanf(line + mac_position, MAC_ADDRESS_FORMAT,
                           &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
                    char bssid[32];
                    snprintf(bssid, sizeof(bssid), "%02x:%02x:%02x:%02x:%02x:%02x",
                             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

                    trim_whitespace(ssid);
                    int count_word_ssid = count_words(ssid);
                    if(count_word_ssid > 0){
                        cJSON *ap = cJSON_CreateObject();
                        cJSON_AddStringToObject(ap, "SSID", ssid);
                        cJSON_AddStringToObject(ap, "BSSID", bssid);
                        cJSON_AddItemToArray(ap_list, ap);
                    }
                }
            }
        }
    }
    cJSON_AddItemToObject(root, "List AP", ap_list);
    char *json_string = cJSON_Print(root);
    if (json_string) {
        printf_json_in_file(output_file,json_string);
        printf("%s\n", json_string);
        free(json_string);
    }
    cJSON_Delete(root);
    fclose(file);
}

void scan_and_write_wifi_5G(){
    system(SITE_SURVEY_5G);
    sleep(WAITING_TIME_SCAN);
    system(WRITE_5G_TO_FILE);
}

void scan_and_write_wifi_2G(){
    system(SITE_SURVEY_2G);
    sleep(WAITING_TIME_SCAN);
    system(WRITE_2G_TO_FILE);
}

void scan_and_write_all(){
    system(SITE_SURVEY_2G);
    sleep(WAITING_TIME_SCAN);
    system(WRITE_2G_TO_FILE);
    system(SITE_SURVEY_5G);
    sleep(WAITING_TIME_SCAN);
    system(INSERT_5G_TO_FILE);
}


void scan_wifi_when_start(){
    printf("Please wait a moment !\n");
    scan_and_write_all();
}

