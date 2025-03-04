#ifndef __DSL_LIST_H
#define __DSL_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../dsl.h"

typedef struct dsl_list_node_t
{
    void *data;
    struct dsl_list_node_t *next;
    struct dsl_list_node_t *last;
} dsl_list_node_t;

typedef dsl_list_node_t * dsl_list_node_handle_t;

typedef struct
{
    dsl_list_node_t *head;
    dsl_list_node_t *tail;
    size_t data_size;
    int length;
} dsl_list_t;

typedef dsl_list_t * dsl_list_handle_t;

dsl_list_handle_t dsl_list_create_list(size_t data_size);
void dsl_list_delete_list(dsl_list_handle_t list);
dsl_list_node_handle_t dsl_list_create_node(size_t data_size);
void dsl_list_delete_node(dsl_list_node_handle_t node);
void dsl_list_insert_at_head(dsl_list_handle_t list, dsl_list_node_handle_t node);
void dsl_list_insert_at_tail(dsl_list_handle_t list, dsl_list_node_handle_t node);
void dsl_list_insert(dsl_list_handle_t list, int index, dsl_list_node_handle_t node);
void dsl_list_remove_at_head(dsl_list_handle_t list, dsl_list_node_handle_t *removed_node);
void dsl_list_remove_at_tail(dsl_list_handle_t list, dsl_list_node_handle_t *removed_node);
void dsl_list_remove(dsl_list_handle_t list, int index, dsl_list_node_handle_t *removed_node);
dsl_list_node_handle_t dsl_list_add(dsl_list_handle_t list, int index, void *data);
void dsl_list_delete(dsl_list_handle_t list, int index);
dsl_list_node_handle_t dsl_list_modify(dsl_list_handle_t list, int index, void *data);
dsl_list_node_handle_t dsl_list_extract(dsl_list_handle_t list, int index, void *data);

#ifdef __cplusplus
}
#endif

#endif