/**
 * @file
 * @brief Doubly-linked list implementation
 *
 * Doubly-linked list implementation using inline macros/functions.
 * This API is not thread safe, and thus if a list is used across threads,
 * calls to functions must be protected with synchronization primitives.
 *
 * The lists are expected to be initialized such that both the head and tail
 * pointers point to the list itself.  Initializing the lists in such a fashion
 * simplifies the adding and removing of nodes to/from the list.
 */

#ifndef _EASY_DLIST_H_
#define _EASY_DLIST_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup doubly-linked-list_apis Doubly-linked list
 * @ingroup datastructure_apis
 * @{
 */

struct _easy_dnode
{
    union
    {
        struct _easy_dnode *head; /* ptr to head of list (easy_dlist_t) */
        struct _easy_dnode *next; /* ptr to next node    (easy_dnode_t) */
    };
    union
    {
        struct _easy_dnode *tail; /* ptr to tail of list (easy_dlist_t) */
        struct _easy_dnode *prev; /* ptr to previous node (easy_dnode_t) */
    };
};

typedef struct _easy_dnode easy_dlist_t;
typedef struct _easy_dnode easy_dnode_t;

/**
 * @brief Provide the primitive to iterate on a list
 * Note: the loop is unsafe and thus __dn should not be removed
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     EASY_DLIST_FOR_EACH_NODE(l, n) {
 *         <user code>
 *     }
 *
 * This and other EASY_DLIST_*() macros are not thread safe.
 *
 * @param __dl A pointer on a easy_dlist_t to iterate on
 * @param __dn A easy_dnode_t pointer to peek each node of the list
 */
#define EASY_DLIST_FOR_EACH_NODE(__dl, __dn) for (__dn = easy_dlist_peek_head(__dl); __dn != NULL; __dn = easy_dlist_peek_next(__dl, __dn))

/**
 * @brief Provide the primitive to iterate on a list, from a node in the list
 * Note: the loop is unsafe and thus __dn should not be removed
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     EASY_DLIST_ITERATE_FROM_NODE(l, n) {
 *         <user code>
 *     }
 *
 * Like EASY_DLIST_FOR_EACH_NODE(), but __dn already contains a node in the list
 * where to start searching for the next entry from. If NULL, it starts from
 * the head.
 *
 * This and other EASY_DLIST_*() macros are not thread safe.
 *
 * @param __dl A pointer on a easy_dlist_t to iterate on
 * @param __dn A easy_dnode_t pointer to peek each node of the list;
 *             it contains the starting node, or NULL to start from the head
 */
#define EASY_DLIST_ITERATE_FROM_NODE(__dl, __dn)                                                                                                               \
    for (__dn = __dn ? easy_dlist_peek_next_no_check(__dl, __dn) : easy_dlist_peek_head(__dl); __dn != NULL; __dn = easy_dlist_peek_next(__dl, __dn))

/**
 * @brief Provide the primitive to safely iterate on a list
 * Note: __dn can be removed, it will not break the loop.
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     EASY_DLIST_FOR_EACH_NODE_SAFE(l, n, s) {
 *         <user code>
 *     }
 *
 * This and other EASY_DLIST_*() macros are not thread safe.
 *
 * @param __dl A pointer on a easy_dlist_t to iterate on
 * @param __dn A easy_dnode_t pointer to peek each node of the list
 * @param __dns A easy_dnode_t pointer for the loop to run safely
 */
#define EASY_DLIST_FOR_EACH_NODE_SAFE(__dl, __dn, __dns)                                                                                                       \
    for (__dn = easy_dlist_peek_head(__dl), __dns = easy_dlist_peek_next(__dl, __dn); __dn != NULL; __dn = __dns, __dns = easy_dlist_peek_next(__dl, __dn))

/*
 * @brief Provide the primitive to resolve the container of a list node
 * Note: it is safe to use with NULL pointer nodes
 *
 * @param __dn A pointer on a easy_dnode_t to get its container
 * @param __cn Container struct type pointer
 * @param __n The field name of easy_dnode_t within the container struct
 */
#define EASY_DLIST_CONTAINER(__dn, __cn, __n)           ((__dn != NULL) ? CONTAINER_OF(__dn, __typeof__(*__cn), __n) : NULL)
/*
 * @brief Provide the primitive to peek container of the list head
 *
 * @param __dl A pointer on a easy_dlist_t to peek
 * @param __cn Container struct type pointer
 * @param __n The field name of easy_dnode_t within the container struct
 */
#define EASY_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n) EASY_DLIST_CONTAINER(easy_dlist_peek_head(__dl), __cn, __n)

/*
 * @brief Provide the primitive to peek the next container
 *
 * @param __dl A pointer on a easy_dlist_t to peek
 * @param __cn Container struct type pointer
 * @param __n The field name of easy_dnode_t within the container struct
 */
#define EASY_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n) ((__cn != NULL) ? EASY_DLIST_CONTAINER(easy_dlist_peek_next(__dl, &(__cn->__n)), __cn, __n) : NULL)

/**
 * @brief Provide the primitive to iterate on a list under a container
 * Note: the loop is unsafe and thus __cn should not be detached
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     EASY_DLIST_FOR_EACH_CONTAINER(l, c, n) {
 *         <user code>
 *     }
 *
 * @param __dl A pointer on a easy_dlist_t to iterate on
 * @param __cn A pointer to peek each entry of the list
 * @param __n The field name of easy_dnode_t within the container struct
 */
#define EASY_DLIST_FOR_EACH_CONTAINER(__dl, __cn, __n)                                                                                                         \
    for (__cn = EASY_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n); __cn != NULL; __cn = EASY_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n))

/**
 * @brief Provide the primitive to safely iterate on a list under a container
 * Note: __cn can be detached, it will not break the loop.
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     EASY_DLIST_FOR_EACH_CONTAINER_SAFE(l, c, cn, n) {
 *         <user code>
 *     }
 *
 * @param __dl A pointer on a easy_dlist_t to iterate on
 * @param __cn A pointer to peek each entry of the list
 * @param __cns A pointer for the loop to run safely
 * @param __n The field name of easy_dnode_t within the container struct
 */
#define EASY_DLIST_FOR_EACH_CONTAINER_SAFE(__dl, __cn, __cns, __n)                                                                                             \
    for (__cn = EASY_DLIST_PEEK_HEAD_CONTAINER(__dl, __cn, __n), __cns = EASY_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n); __cn != NULL;                        \
         __cn = __cns, __cns = EASY_DLIST_PEEK_NEXT_CONTAINER(__dl, __cn, __n))

/**
 * @brief initialize list to its empty state
 *
 * @param list the doubly-linked list
 */

static inline void easy_dlist_init(easy_dlist_t *list)
{
    list->head = (easy_dnode_t *)list;
    list->tail = (easy_dnode_t *)list;
}

#define EASY_DLIST_STATIC_INIT(ptr_to_list)                                                                                                                    \
    {                                                                                                                                                          \
        {(ptr_to_list)},                                                                                                                                       \
        {                                                                                                                                                      \
            (ptr_to_list)                                                                                                                                      \
        }                                                                                                                                                      \
    }

/**
 * @brief initialize node to its state when not in a list
 *
 * @param node the node
 */

static inline void easy_dnode_init(easy_dnode_t *node)
{
    node->next = NULL;
    node->prev = NULL;
}

/**
 * @brief check if a node is a member of any list
 *
 * @param node the node
 *
 * @return true if node is linked into a list, false if it is not
 */

static inline bool easy_dnode_is_linked(const easy_dnode_t *node)
{
    return node->next != NULL;
}

/**
 * @brief check if a node is the list's head
 *
 * @param list the doubly-linked list to operate on
 * @param node the node to check
 *
 * @return true if node is the head, false otherwise
 */

static inline bool easy_dlist_is_head(easy_dlist_t *list, easy_dnode_t *node)
{
    return list->head == node;
}

/**
 * @brief check if a node is the list's tail
 *
 * @param list the doubly-linked list to operate on
 * @param node the node to check
 *
 * @return true if node is the tail, false otherwise
 */

static inline bool easy_dlist_is_tail(easy_dlist_t *list, easy_dnode_t *node)
{
    return list->tail == node;
}

/**
 * @brief check if the list is empty
 *
 * @param list the doubly-linked list to operate on
 *
 * @return true if empty, false otherwise
 */

static inline bool easy_dlist_is_empty(easy_dlist_t *list)
{
    return list->head == list;
}

/**
 * @brief check if more than one node present
 *
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param list the doubly-linked list to operate on
 *
 * @return true if multiple nodes, false otherwise
 */

static inline bool easy_dlist_has_multiple_nodes(easy_dlist_t *list)
{
    return list->head != list->tail;
}

/**
 * @brief get a reference to the head item in the list
 *
 * @param list the doubly-linked list to operate on
 *
 * @return a pointer to the head element, NULL if list is empty
 */

static inline easy_dnode_t *easy_dlist_peek_head(easy_dlist_t *list)
{
    return easy_dlist_is_empty(list) ? NULL : list->head;
}

/**
 * @brief get a reference to the head item in the list
 *
 * The list must be known to be non-empty.
 *
 * @param list the doubly-linked list to operate on
 *
 * @return a pointer to the head element
 */

static inline easy_dnode_t *easy_dlist_peek_head_not_empty(easy_dlist_t *list)
{
    return list->head;
}

/**
 * @brief get a reference to the next item in the list, node is not NULL
 *
 * Faster than easy_dlist_peek_next() if node is known not to be NULL.
 *
 * @param list the doubly-linked list to operate on
 * @param node the node from which to get the next element in the list
 *
 * @return a pointer to the next element from a node, NULL if node is the tail
 */

static inline easy_dnode_t *easy_dlist_peek_next_no_check(easy_dlist_t *list, easy_dnode_t *node)
{
    return (node == list->tail) ? NULL : node->next;
}

/**
 * @brief get a reference to the next item in the list
 *
 * @param list the doubly-linked list to operate on
 * @param node the node from which to get the next element in the list
 *
 * @return a pointer to the next element from a node, NULL if node is the tail
 * or NULL (when node comes from reading the head of an empty list).
 */

static inline easy_dnode_t *easy_dlist_peek_next(easy_dlist_t *list, easy_dnode_t *node)
{
    return (node != NULL) ? easy_dlist_peek_next_no_check(list, node) : NULL;
}

/**
 * @brief get a reference to the previous item in the list, node is not NULL
 *
 * Faster than easy_dlist_peek_prev() if node is known not to be NULL.
 *
 * @param list the doubly-linked list to operate on
 * @param node the node from which to get the previous element in the list
 *
 * @return a pointer to the previous element from a node, NULL if node is the
 *	   tail
 */

static inline easy_dnode_t *easy_dlist_peek_prev_no_check(easy_dlist_t *list, easy_dnode_t *node)
{
    return (node == list->head) ? NULL : node->prev;
}

/**
 * @brief get a reference to the previous item in the list
 *
 * @param list the doubly-linked list to operate on
 * @param node the node from which to get the previous element in the list
 *
 * @return a pointer to the previous element from a node, NULL if node is the
 * 	   tail or NULL (when node comes from reading the head of an empty
 * 	   list).
 */

static inline easy_dnode_t *easy_dlist_peek_prev(easy_dlist_t *list, easy_dnode_t *node)
{
    return (node != NULL) ? easy_dlist_peek_prev_no_check(list, node) : NULL;
}

/**
 * @brief get a reference to the tail item in the list
 *
 * @param list the doubly-linked list to operate on
 *
 * @return a pointer to the tail element, NULL if list is empty
 */

static inline easy_dnode_t *easy_dlist_peek_tail(easy_dlist_t *list)
{
    return easy_dlist_is_empty(list) ? NULL : list->tail;
}

/**
 * @brief add node to tail of list
 *
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param list the doubly-linked list to operate on
 * @param node the element to append
 */

static inline void easy_dlist_append(easy_dlist_t *list, easy_dnode_t *node)
{
    easy_dnode_t *const tail = list->tail;

    node->next = list;
    node->prev = tail;

    tail->next = node;
    list->tail = node;
}

/**
 * @brief add node to head of list
 *
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param list the doubly-linked list to operate on
 * @param node the element to append
 */

static inline void easy_dlist_prepend(easy_dlist_t *list, easy_dnode_t *node)
{
    easy_dnode_t *const head = list->head;

    node->next = head;
    node->prev = list;

    head->prev = node;
    list->head = node;
}

/**
 * @brief Insert a node into a list
 *
 * Insert a node before a specified node in a dlist.
 *
 * @param successor the position before which "node" will be inserted
 * @param node the element to insert
 */
static inline void easy_dlist_insert(easy_dnode_t *successor, easy_dnode_t *node)
{
    easy_dnode_t *const prev = successor->prev;

    node->prev = prev;
    node->next = successor;
    prev->next = node;
    successor->prev = node;
}

/**
 * @brief insert node at position
 *
 * Insert a node in a location depending on a external condition. The cond()
 * function checks if the node is to be inserted _before_ the current node
 * against which it is checked.
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param list the doubly-linked list to operate on
 * @param node the element to insert
 * @param cond a function that determines if the current node is the correct
 *             insert point
 * @param data parameter to cond()
 */

static inline void easy_dlist_insert_at(easy_dlist_t *list, easy_dnode_t *node, int (*cond)(easy_dnode_t *node, void *data), void *data)
{
    if (easy_dlist_is_empty(list))
    {
        easy_dlist_append(list, node);
    }
    else
    {
        easy_dnode_t *pos = easy_dlist_peek_head(list);

        while ((pos != NULL) && (cond(pos, data) == 0))
        {
            pos = easy_dlist_peek_next(list, pos);
        }
        if (pos != NULL)
        {
            easy_dlist_insert(pos, node);
        }
        else
        {
            easy_dlist_append(list, node);
        }
    }
}

/**
 * @brief remove a specific node from a list
 *
 * The list is implicit from the node. The node must be part of a list.
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param node the node to remove
 */

static inline void easy_dlist_remove(easy_dnode_t *node)
{
    easy_dnode_t *const prev = node->prev;
    easy_dnode_t *const next = node->next;

    prev->next = next;
    next->prev = prev;
    easy_dnode_init(node);
}

/**
 * @brief get the first node in a list
 *
 * This and other easy_dlist_*() functions are not thread safe.
 *
 * @param list the doubly-linked list to operate on
 *
 * @return the first node in the list, NULL if list is empty
 */

static inline easy_dnode_t *easy_dlist_get(easy_dlist_t *list)
{
    easy_dnode_t *node = NULL;

    if (!easy_dlist_is_empty(list))
    {
        node = list->head;
        easy_dlist_remove(node);
    }

    return node;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _BT_DLIST_H_ */