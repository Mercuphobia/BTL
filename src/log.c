#include "log.h"

const char *log_level_strings[] =
    {
        "NONE",
        "ERROR",
        "WARN",
        "DEBUG"};

unsigned char log_run_level;
char buffer[1000];
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

void printf_log(int level, const char *format, ...)
{

  if (level == log_run_level)
  {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("[%s] %s",log_level_strings[level], buffer);
    //printf("[%s] %s:%d: %s\n", log_level_strings[level], __func__, __LINE__, buffer);
    // printf("%s", buffer);
    // fprintf(LOG_FP, "[%s] %s:%d: ", log_level_strings[level], __FUNCTION__, __LINE__);
    // vfprintf(LOG_FP, fmt, args);  // Sử dụng vfprintf để xử lý chuỗi định dạng và các đối số
    // fprintf(LOG_FP, "\n");
    // fprintf(fp, "%s", buffer);
    // fflush(LOG_FP);
    va_end(args);
  }
}