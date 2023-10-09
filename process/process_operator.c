/**
 * @file process_operator.c
 * @brief Process Operator Implementation File
 * @author moecly
 */

#include "process_operator.h"
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Start a new process.
 *
 * This function forks a new process and executes the provided command.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val process_start_handler(struct process_opr *opr) {
  pid_t pid;

  if (opr->info.status != process_status_stop)
    return ret_err;

  pid = fork();
  opr->info.pid = pid;
  opr->info.status = process_status_running;

  if (pid == -1)
    return ret_err;

  if (pid != 0)
    return ret_ok;

  execv(opr->info.args[0], opr->info.args);
  return ret_ok;
}

/**
 * @brief Suspend a running process.
 *
 * This function suspends a running process by sending a SIGSTOP signal.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val process_suspend_handler(struct process_opr *opr) {
  if (opr->info.status == process_status_running) {
    kill(opr->info.pid, SIGSTOP);
    opr->info.status = process_status_pause;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief Resume a paused process.
 *
 * This function resumes a paused process by sending a SIGCONT signal.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val process_resume_handler(struct process_opr *opr) {
  if (opr->info.status == process_status_pause) {
    kill(opr->info.pid, SIGCONT);
    opr->info.status = process_status_running;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief Exit a running process.
 *
 * This function exits a running process by sending a SIGKILL signal.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val process_exit_handler(struct process_opr *opr) {
  if (opr->info.status != process_status_stop) {
    kill(opr->info.pid, SIGKILL);
    opr->info.status = process_status_stop;
    return ret_ok;
  }
  return ret_err;
}

/**
 * @brief Initialize a process operator.
 *
 * This function initializes a process operator with default values.
 *
 * @param opr Pointer to the process operator.
 */
void process_opr_init(process_opr *opr) {
  opr->start = process_start_handler;
  opr->suspend = process_suspend_handler;
  opr->resume = process_resume_handler;
  opr->exit = process_exit_handler;
  opr->info.status = process_status_stop;
  opr->info.pid = -1;
}

/**
 * @brief Set the executable and its arguments for a process operator.
 *
 * This function sets the executable and its arguments for a process operator.
 *
 * @param opr Pointer to the process operator.
 * @param args An array of strings representing the arguments.
 */
void set_process_exec(process_opr *opr, char *args[]) { opr->info.args = args; }

/**
 * @brief Start a process.
 *
 * This function starts a new process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_start(process_opr *opr) { return opr->start(opr); }

/**
 * @brief Suspend a running process.
 *
 * This function suspends a running process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_suspend(process_opr *opr) { return opr->suspend(opr); }

/**
 * @brief Resume a paused process.
 *
 * This function resumes a paused process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_resume(process_opr *opr) { return opr->resume(opr); }

/**
 * @brief Exit a running process.
 *
 * This function exits a running process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val process_exit(process_opr *opr) { return opr->exit(opr); }

/**
 * @brief Wait for a process to finish.
 *
 * This function waits for a process to finish and retrieves its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 * @param options Additional wait options.
 */
void process_wait(process_opr *opr, int *status, int options) {
  if (validate_pointer(opr) == ret_null_pointer)
    wait(status);
  else
    waitpid(opr->info.pid, status, options);
}

/**
 * @brief Wait for a process to finish without blocking.
 *
 * This function waits for a process to finish without blocking and retrieves
 * its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 */
void process_wait_unblock(process_opr *opr, int *status) {
  process_wait(opr, status, WNOHANG);
}

/**
 * @brief Wait for a process to finish and block until it does.
 *
 * This function waits for a process to finish and blocks until it does, then
 * retrieves its exit status.
 *
 * @param opr Pointer to the process operator.
 * @param status Pointer to an integer to store the exit status.
 */
void process_wait_block(process_opr *opr, int *status) {
  process_wait(opr, status, 0);
}

/**
 * @brief Get the Process ID (PID) of a process.
 *
 * This function retrieves the Process ID (PID) of a process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns the PID of the process.
 */
int process_get_pid(process_opr *opr) { return opr->info.pid; }

/**
 * @brief Get the status of a process.
 *
 * This function retrieves the status of a process.
 *
 * @param opr Pointer to the process operator.
 * @return Returns the status of the process.
 */
process_status process_get_status(process_opr *opr) { return opr->info.status; }
