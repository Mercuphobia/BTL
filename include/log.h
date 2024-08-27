#ifndef __LOG_H__
#define __LOG_H__
#include <stdarg.h> 
#include <stdio.h>
#include <stdlib.h>


void log_set_level(int level);
extern const char* log_level_strings[];
void printf_log(int level,const char* format, ...);

#define LOG(level, fmt, ...)  printf_log(level, fmt, __VA_ARGS__)
#define LOG_LVL_NONE  0
#define LOG_LVL_ERROR 1
#define LOG_LVL_WARN  2
#define LOG_LVL_DEBUG 3

#endif /*__LOG_H__*/

