/**
 * @brief: 系统时间模块，提供获取当前小时和分钟的函数
 * @file: sys_time.c
 * @author: moecly
 */

#include "sys_time.h"

static time_t currentTime;
static struct tm *localTime;

/**
 * @brief: 获取当前系统时间的小时
 * @return: 当前小时
 */
int get_hour(void) {
  /* 获取当前系统时间 */
  currentTime = time(NULL);

  /* 将当前时间转换为本地时间结构体 */
  localTime = localtime(&currentTime);

  /* 获取小时 */
  int res = localTime->tm_hour;
  return res;
}

/**
 * @brief: 获取当前系统时间的分钟
 * @return: 当前分钟
 */
int get_minute(void) {
  /* 获取当前系统时间 */
  currentTime = time(NULL);

  /* 将当前时间转换为本地时间结构体 */
  localTime = localtime(&currentTime);

  /* 获取分钟 */
  int res = localTime->tm_min;
  return res;
}
