/**
 * @brief: 日志消息处理模块，提供不同级别的日志输出函数
 * @file: log_msg.c
 * @author: moecly
 */

#include "../inc/log_msg.h"

/* 默认日志输出级别为 DEBUG */
static LOG_LEVEL level = LOG_ERROR;

/**
 * @brief: 输出日志消息
 * @param lv: 日志级别
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void log_msg(LOG_LEVEL lv, const char *format, ...) {
  /* 如果日志级别高于设定的输出级别，直接返回 */
  if (lv > level)
    return;

  /* 使用可变参数列表打印日志消息 */
  PRINT_LOG(format);
}

/**
 * @brief: 输出 DEBUG 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void dlog(const char *format, ...) {
  /* 如果日志级别低于 DEBUG，直接返回 */
  if (level < LOG_DEBUG)
    return;

  /* 使用可变参数列表打印 DEBUG 级别日志消息 */
  PRINT_LOG(format);
}

/**
 * @brief: 输出 ERROR 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void elog(const char *format, ...) {
  /* 如果日志级别低于 ERROR，直接返回 */
  if (level < LOG_ERROR)
    return;

  /* 使用可变参数列表打印 ERROR 级别日志消息 */
  PRINT_LOG(format);
}

/**
 * @brief: 输出 WARNING 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void wlog(const char *format, ...) {
  /* 如果日志级别低于 WARNING，直接返回 */
  if (level < LOG_WARNING)
    return;

  /* 使用可变参数列表打印 WARNING 级别日志消息 */
  PRINT_LOG(format);
}

/**
 * @brief: 输出 INFO 级别日志消息
 * @param format: 格式化字符串
 * @param ...: 可变参数列表
 */
void ilog(const char *format, ...) {
  /* 如果日志级别低于 INFO，直接返回 */
  if (level < LOG_INFO)
    return;

  /* 使用可变参数列表打印 INFO 级别日志消息 */
  PRINT_LOG(format);
}
