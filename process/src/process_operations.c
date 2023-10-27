/**
 * @file process_operations.c
 * @brief 进程操作实现文件
 * @author moecly
 */

#include "../inc/process_operations.h"
#include "c-utils/common/inc/common.h"
#include "c-utils/log_msg/inc/log_msg.h"
#include "stdlib.h"
#include <sys/wait.h>
#include <unistd.h>

static process_operations *ops = NULL;

/**
 * @brief 设置进程的命令行参数
 *
 * @param info 进程信息结构体指针
 * @param args 命令行参数数组
 */
void set_process_exec(process_info *info, char *args[]) { info->args = args; }

/**
 * @brief 启动进程
 *
 * @param info 进程信息结构体指针
 * @return 启动结果
 */
ret_val process_start(process_info *info) { return ops->start(info); }

/**
 * @brief 暂停进程
 *
 * @param info 进程信息结构体指针
 * @return 暂停结果
 */
ret_val process_suspend(process_info *info) { return ops->suspend(info); }

/**
 * @brief 恢复进程
 *
 * @param info 进程信息结构体指针
 * @return 恢复结果
 */
ret_val process_resume(process_info *info) { return ops->resume(info); }

/**
 * @brief 终止进程
 *
 * @param info 进程信息结构体指针
 * @return 终止结果
 */
ret_val process_exit(process_info *info) { return ops->exit(info); }

/**
 * @brief 阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 */
void process_wait_block(process_info *info, int *status) {
  ops->wait_block(info, status);
}

/**
 * @brief 非阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 */
void process_wait_unblock(process_info *info, int *status) {
  ops->wait_unblock(info, status);
}

/**
 * @brief 获取进程的ID
 *
 * @param info 进程信息结构体指针
 * @return 进程ID
 */
int process_get_pid(process_info *info) { return info->pid; }

/**
 * @brief 获取进程状态
 *
 * @param info 进程信息结构体指针
 * @return 进程状态
 */
process_status process_get_status(process_info *info) { return info->status; }

/**
 * @brief 创建进程信息结构体
 *
 * @return 创建的进程信息结构体
 */
process_info create_process_info(void) {
  process_info info;
  info.status = process_status_stop;
  return info;
}

/**
 * @brief 初始化进程操作
 *
 * @return 初始化结果
 */
ret_val process_ops_init(void) {
  ret_val ret;

  ret = validate_pointer(ops);
  if (ret == ret_ok)
    return ret;

#ifdef LINUX_OS
  extern ret_val linux_process_ops_init(process_operations * *ops);
  ret = linux_process_ops_init(&ops);
#endif

  return ret;
}

/**
 * @brief 重置进程操作
 *
 * @return 重置结果
 */
ret_val process_ops_reset(void) {
  ret_val ret;
  ret = validate_pointer(ops);
  if (ret == ret_ok)
    FREE_FUNC(ops);
  return ret;
}
