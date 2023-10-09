/**
 * @brief: 日志消息处理模块，提供不同级别的日志输出函数
 * @file: log_msg.h
 * @author: moecly
 */

#ifndef __LOG_MSG_H_
#define __LOG_MSG_H_

#include "stdarg.h"
#include "stdio.h"

/**
 * @brief: 定义不同的日志级别
 */
typedef enum {
  LOG_INFO,
  LOG_WARNING,
  LOG_DEBUG,
  LOG_ERROR,
} LOG_LEVEL;

/**
 * @brief: 格式化输出日志消息
 * @param format: 格式化字符串
 */
#define PRINT_LOG(format)                                                      \
  va_list format##_args;                                                       \
  va_start(format##_args, format);                                             \
  vprintf(format, format##_args);                                              \
  va_end(format##_args);

/**
 * @brief: 输出当前调试信息到日志（DEBUG级别）
 */
#define DLOG_CURR()                                                            \
  dlog("debug file: %s function: %s line: %d\n", __FILE__, __FUNCTION__,       \
       __LINE__);

/**
 * @brief: 输出当前错误信息到日志（ERROR级别）
 */
#define ELOG_CURR()                                                            \
  elog("error file: %s function: %s line: %d\n", __FILE__, __FUNCTION__,       \
       __LINE__);

/**
 * @brief: 输出当前警告信息到日志（WARNING级别）
 */
#define WLOG_CURR()                                                            \
  wlog("warning file: %s function: %s line: %d\n", __FILE__, __FUNCTION__,     \
       __LINE__);

/**
 * @brief: 输出当前信息到日志（INFO级别）
 */
#define ILOG_CURR()                                                            \
  ilog("info file: %s function: %s line: %d\n", __FILE__, __FUNCTION__,        \
       __LINE__);

/**
 * @brief: 输出日志消息
 * @param lv: 日志级别
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void log_msg(LOG_LEVEL lv, const char *format, ...);

/**
 * @brief: 输出 DEBUG 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void dlog(const char *format, ...);

/**
 * @brief: 输出 ERROR 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void elog(const char *format, ...);

/**
 * @brief: 输出 WARNING 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void wlog(const char *format, ...);

/**
 * @brief: 输出 INFO 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void ilog(const char *format, ...);

#endif // !__LOG_MSG_H_
