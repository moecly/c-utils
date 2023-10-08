/**
 * @file process_operator.h
 * @brief Process Operator Header File
 * @author moecly
 */

#ifndef __PROCESS_OPERATOR_H_
#define __PROCESS_OPERATOR_H_

#include "c-utils/c-utils.h"
#include <signal.h>

/**
 * @brief Enum representing the status of a process.
 */
typedef enum {
  process_status_running, /**< The process is running. */
  process_status_pause,   /**< The process is paused. */
  process_status_stop     /**< The process is stopped. */
} process_status;

/**
 * @brief Structure containing information about a process.
 */
typedef struct {
  pid_t pid;             /**< The Process ID (PID). */
  char **args;           /**< An array of strings representing the arguments. */
  process_status status; /**< The status of the process. */
} process_info;

/**
 * @brief Structure representing a process operator.
 */
typedef struct process_opr {
  ret_val (*start)(
      struct process_opr *opr); /**< Function pointer to start a process. */
  ret_val (*suspend)(
      struct process_opr *opr); /**< Function pointer to suspend a process. */
  ret_val (*resume)(
      struct process_opr *opr); /**< Function pointer to resume a process. */
  ret_val (*exit)(
      struct process_opr *opr); /**< Function pointer to exit a process. */
  process_info info;            /**< Information about the process. */
} process_opr;

/**
 * @brief Initialize a process operator.
 *
 * This function initializes a process operator with default values.
 *
 * @param opr Pointer to the process operator.
 */
void process_opr_init(process_opr *opr);

/**
 * @brief Set the executable and its arguments for a process operator.
 *
 * This function sets the executable and its arguments for a process operator.
 *
 * @param opr Pointer to the process operator.
 * @param args An array of strings representing the arguments.
 */
void set_process_exec(process_opr *opr, char *args[]);

/**
 * @brief Start a process.
 *
 * This function starts a new process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_start(process_opr *opr);

/**
 * @brief Suspend a running process.
 *
 * This function suspends a running process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_suspend(process_opr *opr);

/**
 * @brief Resume a paused process.
 *
 * This function resumes a paused process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_resume(process_opr *opr);

/**
 * @brief Exit a running process.
 *
 * This function exits a running process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_exit(process_opr *opr);

/**
 * @brief Wait for a process to finish.
 *
 * This function waits for a process to finish and retrieves its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 * @param options Additional wait options.
 */
void process_wait(process_opr *opr, int *status, int options);

/**
 * @brief Wait for a process to finish without blocking.
 *
 * This function waits for a process to finish without blocking and retrieves
 * its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 */
void process_wait_unblock(process_opr *opr, int *status);

/**
 * @brief Wait for a process to finish and block until it does.
 *
 * This function waits for a process to finish and blocks until it does, then
 * retrieves its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 */
void process_wait_block(process_opr *opr, int *status);

/**
 * @brief Get the Process ID (PID) of a process.
 *
 * This function retrieves the Process ID (PID) of a process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns the PID of the process.
 */
int process_get_pid(process_opr *opr);

#endif // !__PROCESS_OPERATOR_H_
