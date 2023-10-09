/**
 * @brief: 字符串工具模块，提供字符串处理相关函数
 * @file: str_util.c
 * @author: moecly
 */

#include "../inc/str_util.h"

/**
 * @brief: 将整数转换为字符串
 * @param str: 存储转换结果的字符串
 * @param num: 要转换的整数
 */
void int_num_to_str(char *str, int num) {
  sprintf(str, "%d", num); /* 将数字转换为字符串 */
}
