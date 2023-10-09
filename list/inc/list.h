/**
 * @brief: 自定义链表头文件，提供链表操作函数和相关宏定义
 * @file: list.h
 * @author: moecly
 */

#ifndef __LIST_H_
#define __LIST_H_

#include "stdlib.h"
#include <stdint.h>

/**
 * @brief: 链表节点结构定义
 */
typedef struct list_node {
  struct list_node *prev; /* 指向前一个节点 */
  struct list_node *next; /* 指向后一个节点 */
  void *val;              /* 节点存储的值 */
} list_node;

/**
 * @brief: 链表结构定义
 */
typedef struct {
  list_node *head; /* 链表头节点 */
  list_node *tail; /* 链表尾节点 */
  uint32_t len;    /* 链表长度 */
} pn_list;

#ifndef SET_NODE
#define SET_NODE(src, dst, property) src->property = dst;
#endif // !SET_NODE

#ifndef SET_NODE_NEXT
#define SET_NODE_NEXT(src, dst) SET_NODE(src, dst, next)
#endif // !SET_NODE_NEXT

#ifndef SET_NODE_PREV
#define SET_NODE_PREV(src, dst) SET_NODE(src, dst, prev)
#endif // !SET_NODE_PREV

#ifndef SET_LIST_LEN
#define SET_LIST_LEN(list, length) list->len = length
#endif // !SET_LIST_LEN

#ifndef GET_LIST_LEN
#define GET_LIST_LEN(list) list->len
#endif // !GET_LIST_LEN

#ifndef LIST_HEAD
#define LIST_HEAD(list) (list->head)
#endif // !LIST_HEAD

#ifndef LIST_TAIL
#define LIST_TAIL(list) (list->tail)
#endif // !LIST_TAIL

#ifndef LIST_HEAD_NODE
#define LIST_HEAD_NODE(list) NODE_NEXT(LIST_HEAD(list))
#endif // !LIST_HEAD_NODE

#ifndef LIST_TAIL_NODE
#define LIST_TAIL_NODE(list) NODE_PREV(LIST_TAIL(list))
#endif // !LIST_HEAD_NODE

#ifndef NODE_PREV
#define NODE_PREV(nd) (nd->prev)
#endif // !NODE_PREV

#ifndef NODE_NEXT
#define NODE_NEXT(nd) (nd->next)
#endif // !NODE_PREV

#ifndef NODE_VAL
#define NODE_VAL(nd) (nd->val)
#endif // !NODE_VAL

#ifndef LIST_INIT
#define LIST_INIT(list)                                                        \
  list = MALLOC_FUNC(pn_list);                                                 \
  SET_LIST_LEN(list, 0);                                                       \
  LIST_TAIL(list) = MALLOC_FUNC(list_node);                                    \
  LIST_HEAD(list) = MALLOC_FUNC(list_node);                                    \
  SET_NODE_NEXT(LIST_HEAD(list), LIST_TAIL(list));                             \
  SET_NODE_PREV(LIST_TAIL(list), LIST_HEAD(list));                             \
  SET_NODE_PREV(LIST_HEAD(list), NULL);                                        \
  SET_NODE_NEXT(LIST_TAIL(list), NULL);
#endif // !LIST_INIT

#ifndef LIST_CREATE
#define LIST_CREATE(list) LIST_INIT(list)
#endif // !LIST_CREATE

#ifndef LIST_FREE
#define LIST_FREE(list)                                                        \
  list_node *list##_nd = LIST_HEAD(list);                                      \
  list_node *list##_tmp_nd = list##_nd;                                        \
  while (list##_nd) {                                                          \
    list##_tmp_nd = NODE_NEXT(list##_nd);                                      \
    FREE_FUNC(list##_nd);                                                      \
    list##_nd = list##_tmp_nd;                                                 \
  }                                                                            \
  FREE_FUNC(list)
#endif // !LIST_FREE

/* 定义一个宏，用于遍历链表结构 */
#define each_node_for_list(node, list, property)                               \
  for (node = LIST_HEAD_NODE(list); node != LIST_TAIL(list);                   \
       node = node->property)

/**
 * @brief: 创建一个新的链表
 * @return: 返回一个指向新链表的指针
 */
pn_list *list_new(void);

/**
 * @brief: 释放链表及其节点
 * @param list: 链表指针
 */
void list_free(pn_list *list);

/**
 * @brief: 将节点插入链表头部
 * @param list: 链表指针
 * @param nd: 要插入的节点
 */
void list_push_node_to_head(pn_list *list, list_node *nd);

/**
 * @brief: 将节点插入链表尾部
 * @param list: 链表指针
 * @param nd: 要插入的节点
 */
void list_push_node_to_tail(pn_list *list, list_node *nd);

/**
 * @brief: 在链表头部插入值
 * @param list: 链表指针
 * @param val: 要插入的值
 */
void list_push_to_head(pn_list *list, void *val);

/**
 * @brief: 在链表尾部插入值
 * @param list: 链表指针
 * @param val: 要插入的值
 */
void list_push_to_tail(pn_list *list, void *val);

/**
 * @brief: 从索引获取节点
 * @param list: 链表指针
 * @param idx: 要获取的节点的索引
 * @return: 返回指向节点的指针，如果索引无效返回 NULL
 */
void *list_get_node_from_index(pn_list *list, uint32_t idx);

/**
 * @brief: 从索引获取值
 * @param list: 链表指针
 * @param idx: 要获取的节点的索引
 * @return: 返回指向节点值的指针，如果索引无效返回 NULL
 */
void *list_get_val_from_index(pn_list *list, uint32_t idx);

/**
 * @brief: 获取链表长度
 * @param list: 链表指针
 * @return: 返回链表的长度
 */
uint32_t list_get_length(pn_list *list);

#endif // !__LIST_H_
