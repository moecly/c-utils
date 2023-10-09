/**
 * @file common.c
 * @brief 包含通用函数和声明的实现。
 * @author moecly
 */

#include "../inc/common.h"

/**
 * @brief 验证指针是否有效。
 * @param ptr 待验证的指针。
 * @return 若指针无效，返回ret_null_pointer；否则返回ret_ok。
 */
ret_val validate_pointer(void *ptr) {
  if (!ptr)
    return ret_null_pointer;
  return ret_ok;
}
