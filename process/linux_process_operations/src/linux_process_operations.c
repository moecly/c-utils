/**
 * @file linux_process_operations.c
 * @brief Linux进程操作实现文件
 * @author moecly
 */

#include "../inc/linux_process_operations.h"
#include "c-utils/common/inc/common.h"
#include "stdlib.h"
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief 启动进程
 *
 * @param info 进程信息结构体指针
 * @return 启动结果
 */
static ret_val process_start_handler(process_info *info) {
  pid_t pid;

  if (info->status != process_status_stop)
    return ret_err;

  pid = fork();
  info->pid = pid;
  info->status = process_status_running;

  if (pid == -1)
    return ret_err;

  if (pid != 0)
    return ret_ok;

  execv(info->args[0], info->args);
  return ret_ok;
}

/**
 * @brief 暂停进程
 *
 * @param info 进程信息结构体指针
 * @return 暂停结果
 */
static ret_val process_suspend_handler(process_info *info) {
  if (info->status == process_status_running) {
    kill(info->pid, SIGSTOP);
    info->status = process_status_pause;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief 恢复进程
 *
 * @param info 进程信息结构体指针
 * @return 恢复结果
 */
static ret_val process_resume_handler(process_info *info) {
  if (info->status == process_status_pause) {
    kill(info->pid, SIGCONT);
    info->status = process_status_running;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief 终止进程
 *
 * @param info 进程信息结构体指针
 * @return 终止结果
 */
static ret_val process_exit_handler(process_info *info) {
  if (info->status != process_status_stop) {
    kill(info->pid, SIGKILL);
    info->status = process_status_stop;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief 阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 * @return 等待结果
 */
static ret_val process_wait_block_handler(process_info *info, int *status) {
  waitpid(info->pid, status, 0);
  return ret_ok;
}

/**
 * @brief 非阻塞等待进程退出
 *
 * @param info 进程信息结构体指针
 * @param status 存储退出状态的整数指针
 * @return 等待结果
 */
static ret_val process_wait_unblock_handler(process_info *info, int *status) {
  waitpid(info->pid, status, WNOHANG);
  return ret_ok;
}

/**
 * @brief 初始化Linux进程操作
 *
 * @param ops 用于存储Linux进程操作函数指针的结构体指针
 * @return 初始化结果
 */
ret_val linux_process_ops_init(process_operations **ops) {
  ret_val ret = ret_err;
  if (*ops != NULL)
    return ret_ok;

  *ops = MALLOC_FUNC(process_operations);
  ret = validate_pointer(*ops);
  if (ret != ret_ok)
    return ret;

  (*ops)->start = process_start_handler;
  (*ops)->suspend = process_suspend_handler;
  (*ops)->resume = process_resume_handler;
  (*ops)->exit = process_exit_handler;
  (*ops)->wait_block = process_wait_block_handler;
  (*ops)->wait_unblock = process_wait_unblock_handler;
  return ret;
}
