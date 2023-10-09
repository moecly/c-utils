/**
 * @brief: 系统时间模块，提供获取当前小时和分钟的函数
 * @file: sys_time.h
 * @author: moecly
 */

#ifndef __SYS_TIME_H_
#define __SYS_TIME_H_

#include "time.h"

/**
 * @brief: 获取当前系统时间的小时
 * @return: 当前小时
 */
int get_hour(void);

/**
 * @brief: 获取当前系统时间的分钟
 * @return: 当前分钟
 */
int get_minute(void);

#endif // !__SYS_TIME_H_
