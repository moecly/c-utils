/**
 * @file common.h
 * @brief 包含通用函数和声明的头文件
 * @author moecly
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#ifndef NULL
#define NULL (void *)0
#endif // !NULL

/* 定义一个宏，用于根据属性类型分配内存并返回指针 */
#ifndef MALLOC_FUNC
#define MALLOC_FUNC(property) (property *)malloc(sizeof(property))
#endif // !MALLOC_FUNC

/* 定义一个宏，用于释放内存 */
#ifndef FREE_FUNC
#define FREE_FUNC free
#endif // !FREE_FUNC

/* 定义一个宏，用于标记未使用的变量，防止编译器警告 */
#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif // !UNUSED

/* 定义一个宏，用于计算可变参数的长度 */
#ifndef NUM_ARGS
#define NUM_ARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#endif // !ARRAY_LEN
  
/* 定义一个宏，用于计算数组的长度 */
#ifndef ARRAY_LEN
#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))
#endif // !ARRAY_LEN

/* 定义一个宏，用于遍历链表结构 */
#define each_node_for_linked(node, linked, property)                           \
  for (node = linked; node != NULL; node = node->property)

/* 定义一个宏，用于遍历数组 */
#define each_node_for_array(node, array)                                       \
  size_t array##_length = sizeof(array) / sizeof(array[0]);                    \
  for (size_t array##_index = 0, node = &array[array##_index];                 \
       array##_index < array##_length; array##_index++)

typedef enum {
  ret_ok = 0,
  ret_err,
  ret_null_pointer,
} ret_val;

/**
 * @brief 验证指针是否有效。
 * @param ptr 待验证的指针。
 * @return 若指针无效，返回ret_null_pointer；否则返回ret_ok。
 */
ret_val validate_pointer(void *ptr);

#endif // !__COMMON_H_
