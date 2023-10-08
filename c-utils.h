/**
 * @brief: 通用工具模块，包含各个子模块的头文件引用
 * @file: c-utils.h
 * @author: moecly
 */

#ifndef __C_UTILS_H_
#define __C_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "utils-configs.h"

#ifdef USE_COMMON
#include "common/common.h" /* 引用通用功能模块 */
#endif

#ifdef USE_LIST
#include "list/list.h" /* 引用链表数据结构模块 */
#endif

#ifdef USE_LOG_MSG
#include "log_msg/log_msg.h" /* 引用日志消息模块 */
#endif

#ifdef USE_STR_UTIL
#include "str_util/str_util.h" /* 引用字符串处理工具模块 */
#endif

#ifdef USE_SYS_TIME
#include "sys_time/sys_time.h" /* 引用系统时间模块 */
#endif

#ifdef USE_PROCESS
#include "process/process_operator.h" /* 引用进程管理者模块 */
#endif

#ifdef USE_SOCKET
#include "socket/socket_operator.h" /* 引用进程管理者模块 */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__C_UTILS_H_
