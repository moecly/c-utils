/**
 * @file linux_process_operations.h
 * @brief Linux进程操作头文件
 * @author moecly
 */

#ifndef __LINUX_PROCESS_OPERATIONS_
#define __LINUX_PROCESS_OPERATIONS_

#include "../../inc/process_operations.h"

/**
 * @brief 初始化Linux进程操作
 *
 * @param ops 用于存储Linux进程操作函数指针的结构体指针
 * @return 初始化结果
 */
ret_val linux_process_ops_init(process_operations **ops);

#endif // !__LINUX_PROCESS_OPERATIONS_
