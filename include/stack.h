#pragma once

#include "list.h"
#include "types.h"

struct stack_node {
    struct list_head __node; 
};

#define stack_top_container_of(stack, type, mem) \
    container_of(stack_top(stack), type, mem)

static inline void stack_init(struct stack_node *stack)
{
    INIT_LIST_HEAD(&stack->__node);
}

static inline void stack_push(struct stack_node *stack, struct stack_node *node)
{
    list_add(&stack->__node, &node->__node);
}

static inline void stack_pop(struct stack_node *stack)
{
    list_del(stack->__node.next);
}

static inline struct stack_node *stack_top(struct stack_node *stack)
{
    return (struct stack_node *)(stack->__node.next);
}

static inline bool stack_empty(struct stack_node *stack)
{
    return list_empty(&stack->__node);
}
