/**
 * @file process_operator.h
 * @brief 进程操作头文件
 * @author moecly
 */

#ifndef __PROCESS_OPERATOR_H_
#define __PROCESS_OPERATOR_H_

#include "../../common/inc/common.h"

#define LINUX_OS
#ifdef LINUX_OS
#include <signal.h>
#define process_pid pid_t
#endif

/**
 * @brief 进程状态枚举
 */
typedef enum {
  process_status_running, /**< 进程正在运行 */
  process_status_pause,   /**< 进程已暂停 */
  process_status_stop     /**< 进程已停止 */
} process_status;

/**
 * @brief 进程信息结构体
 */
typedef struct {
  process_pid pid;       /**< 进程ID */
  char **args;           /**< 命令行参数 */
  process_status status; /**< 进程状态 */
} process_info;

/**
 * @brief 进程操作函数指针结构体
 */
typedef struct process_operations {
  ret_val (*start)(process_info *info);   /**< 启动进程 */
  ret_val (*suspend)(process_info *info); /**< 暂停进程 */
  ret_val (*resume)(process_info *info);  /**< 恢复进程 */
  ret_val (*exit)(process_info *info);    /**< 终止进程 */
  ret_val (*wait_block)(process_info *info,
                        int *status); /**< 阻塞等待进程退出 */
  ret_val (*wait_unblock)(process_info *info,
                          int *status); /**< 非阻塞等待进程退出 */
} process_operations;

/**
 * @brief 初始化进程操作
 *
 * @return 初始化结果
 */
ret_val process_ops_init(void);

/**
 * @brief 设置进程的命令行参数
 *
 * @param info 进程信息结构体指针
 * @param args 命令行参数数组
 */
void set_process_exec(process_info *info, char *args[]);

/**
 * @brief 启动进程
 *
 * @param info 进程信息结构体指针
 * @return 启动结果
 */
ret_val process_start(process_info *info);

/**
 * @brief 暂停进程
 *
 * @param info 进程信息结构体指针
 * @return 暂停结果
 */
ret_val process_suspend(process_info *info);

/**
 * @brief 恢复进程
 *
 * @param info 进程信息结构体指针
 * @return 恢复结果
 */
ret_val process_resume(process_info *info);

/**
 * @brief 终止进程
 *
 * @param info 进程信息结构体指针
 * @return 终止结果
 */
ret_val process_exit(process_info *info);

/**
 * @brief 阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 */
void process_wait_block(process_info *info, int *status);

/**
 * @brief 非阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 */
void process_wait_unblock(process_info *info, int *status);

/**
 * @brief 获取进程的ID
 *
 * @param info 进程信息结构体指针
 * @return 进程ID
 */
int process_get_pid(process_info *info);

/**
 * @brief 创建进程信息结构体
 *
 * @return 创建的进程信息结构体
 */
process_info create_process_info(void);

#endif // !__PROCESS_OPERATOR_H_
