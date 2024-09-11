#include "log.h"
#include "file_process.h"
#include "time.h"
#define LOG_FILE_PATH "./data/log.txt"
const char *log_level_strings[] =
    {
        "NONE",
        "ERROR",
        "WARN",
        "DEBUG"};

unsigned char log_run_level;
char buffer[1000];
int is_first_log = 1;
void log_set_level(int level)
{
  if (level >= 0 && level <= 3)
  {
    log_run_level = level;
  }
  else
  {
    printf("Invalid log level. The value to enter is from 0 to 3\n");
    //log_run_level = 1;
  }
}

void get_current_time(char *time_str, size_t size) {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    strftime(time_str, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void printf_log(int level, const char *format, ...)
{
  if (level <= log_run_level)
  {
    char time_str[20];
    get_current_time(time_str, sizeof(time_str));

    FILE *log_file;
    
    if (is_first_log) {
        log_file = open_file(LOG_FILE_PATH, "w");
        is_first_log = 0;
    } else {
        log_file = open_file(LOG_FILE_PATH, "a");
    }

    if (log_file == NULL)
    {
      perror("Failed to open log file");
      return;
    }

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("[%s] %s", log_level_strings[level], buffer);
    fprintf(log_file, "[%s] [%s] %s", time_str, log_level_strings[level], buffer);
    fflush(log_file);
    va_end(args);
    fclose(log_file);
  }
}