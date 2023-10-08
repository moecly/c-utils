/**
 * @file common.c
 * @brief 包含通用函数和声明的实现。
 * @author moecly
 */

#include "common.h"

/**
 * @brief 验证指针是否有效。
 * @param ptr 待验证的指针。
 * @return 若指针无效，返回-1；否则返回0。
 */
ret_val validate_pointer(void *ptr) {
  if (!ptr)
    return ret_err;
  return ret_ok;
}
