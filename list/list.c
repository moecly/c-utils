/**
 * @file list.c
 * @brief 自定义链表实现文件，提供链表操作函数。
 * @author moecly
 */

#include "list.h"
#include <stdint.h>

/**
 * @brief 创建一个新的链表。
 * @return 返回一个指向新链表的指针。
 */
pn_list *list_new(void) {
  pn_list *ret;
  /* 调用宏以创建新链表 */
  LIST_CREATE(ret);
  return ret;
}

/**
 * @brief 释放链表及其节点。
 * @param list 链表指针。
 */
void list_free(pn_list *list) { LIST_FREE(list); }

/**
 * @brief 将节点插入链表头部。
 * @param list 链表指针。
 * @param nd 要插入的节点。
 */
void list_push_node_to_head(pn_list *list, list_node *nd) {
  /* 更新节点的前后关系，增加链表长度 */
  SET_NODE_NEXT(nd, NODE_NEXT(LIST_HEAD(list)));
  SET_NODE_PREV(nd, LIST_HEAD(list));
  SET_NODE_PREV(NODE_NEXT(LIST_HEAD(list)), nd);
  SET_NODE_NEXT(LIST_HEAD(list), nd);
  SET_LIST_LEN(list, GET_LIST_LEN(list) + 1);
}

/**
 * @brief 将节点插入链表尾部。
 * @param list 链表指针。
 * @param nd 要插入的节点。
 */
void list_push_node_to_tail(pn_list *list, list_node *nd) {
  /* 更新节点的前后关系，增加链表长度 */
  SET_NODE_NEXT(nd, LIST_TAIL(list));
  SET_NODE_PREV(nd, NODE_PREV(LIST_TAIL(list)));
  SET_NODE_NEXT(NODE_PREV(LIST_TAIL(list)), nd);
  SET_NODE_PREV(LIST_TAIL(list), nd);
  SET_LIST_LEN(list, GET_LIST_LEN(list) + 1);
}

/**
 * @brief 在链表头部插入值。
 * @param list 链表指针。
 * @param val 要插入的值。
 */
void list_push_to_head(pn_list *list, void *val) {
  /* 创建节点，将值保存在节点中，然后调用 list_push_node_to_head() */
  list_node *nd = MALLOC_FUNC(list_node);
  nd->val = (void *)val;
  list_push_node_to_head(list, nd);
}

/**
 * @brief 在链表尾部插入值。
 * @param list 链表指针。
 * @param val 要插入的值。
 */
void list_push_to_tail(pn_list *list, void *val) {
  /* 创建节点，将值保存在节点中，然后调用 list_push_node_to_tail() */
  list_node *nd = MALLOC_FUNC(list_node);
  nd->val = (void *)val;
  list_push_node_to_tail(list, nd);
}

/**
 * @brief 从索引获取节点。
 * @param list 链表指针。
 * @param idx 要获取的节点的索引。
 * @return 返回指向节点的指针，如果索引无效返回 NULL。
 */
void *list_get_node_from_index(pn_list *list, uint32_t idx) {
  list_node *nd;
  uint32_t index = 0;
  /* 遍历链表，找到对应索引的节点 */
  each_node_for_linked(nd, LIST_HEAD_NODE(list), next) {
    if (index == idx)
      return nd;
    index++;
  }
  return NULL;
}

/**
 * @brief 从索引获取值。
 * @param list 链表指针。
 * @param idx 要获取的节点的索引。
 * @return 返回指向节点值的指针，如果索引无效返回 NULL。
 */
void *list_get_val_from_index(pn_list *list, uint32_t idx) {
  /* 获取对应索引的节点，然后返回节点中的值 */
  list_node *nd = list_get_node_from_index(list, idx);
  if (!nd)
    return NULL;
  return NODE_VAL(nd);
}

/**
 * @brief 获取链表长度。
 * @param list 链表指针。
 * @return 返回链表的长度。
 */
uint32_t list_get_length(pn_list *list) { return GET_LIST_LEN(list); }
