/**
 * @brief: 字符串工具模块，提供字符串处理相关函数
 * @file: str_util.h
 * @author: moecly
 */

#ifndef __STR_UTIL_H_
#define __STR_UTIL_H_

#include "stdio.h"
#include "string.h"

typedef struct {
} str_ops;

typedef struct {
  char *val;
  str_ops ops;
} str_objs;

/**
 * @brief: 将整数转换为字符串
 * @param str: 存储转换结果的字符串
 * @param num: 要转换的整数
 */
void int_num_to_str(char *str, int num);

#endif // !__STR_UTIL_H_