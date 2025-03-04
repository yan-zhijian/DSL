#include "list.h"

dsl_list_handle_t dsl_list_create_list(size_t data_size)
{
    dsl_list_handle_t list = (dsl_list_handle_t)dsl_malloc(sizeof(dsl_list_t));
    if(list)
    {
        list->head = NULL;
        list->tail = NULL;
        list->data_size = data_size;
        list->length = 0;
        return list;
    }
    return NULL;
}

void dsl_list_delete_list(dsl_list_handle_t list)
{
    if(!list) return;
    dsl_list_node_handle_t temp = list->head;
    while(list->head)
    {
        list->head = temp->next;
        dsl_list_delete_node(temp);
    }
    dsl_free(list);
}

dsl_list_node_handle_t dsl_list_create_node(size_t data_size)
{
    dsl_list_node_handle_t node = (dsl_list_node_handle_t)dsl_malloc(sizeof(dsl_list_node_t));
    if(node)
    {
        node->data = dsl_malloc(data_size);
        if(node->data)
        {
            node->next = NULL;
        	node->last = NULL;
            return node;
        }
        else
            dsl_free(node);
    }
    return NULL;
}

void dsl_list_delete_node(dsl_list_node_handle_t node)
{
    if(!node) return;
    dsl_free(node->data);
    dsl_free(node);
}

void dsl_list_insert_at_head(dsl_list_handle_t list, dsl_list_node_handle_t node)
{
    if(!list || !node) return;
    dsl_list_node_handle_t head = list->head;
    node->next = head;
    node->last = NULL;
    if(head)
        head->last = node;
    else
        list->tail = node;
    list->head = node;
    ++list->length;
}

void dsl_list_insert_at_tail(dsl_list_handle_t list, dsl_list_node_handle_t node)
{
    if(!list || !node) return;
    dsl_list_node_handle_t tail = list->tail;
    node->next = NULL;
    node->last = tail;
    if(tail)
        tail->next = node;
    else
        list->head = node;
    list->tail = node;
    ++list->length;
}

void dsl_list_insert(dsl_list_handle_t list, int index, dsl_list_node_handle_t node)
{
    if(!list || !node) return;
    int i = 0;
    dsl_list_node_handle_t temp = NULL;
    if(index == 0 || -index > list->length)
        dsl_list_insert_at_head(list, node);
    else if(index == -1 || index >= list->length)
        dsl_list_insert_at_tail(list, node);
    else
    {
        if(index > 0)
        {
            temp = list->head->next;
            for(i = 1; i < list->length; ++i)
            {
                if(i == index)
                    break;
                temp = temp->next;
            }
            node->next = temp;
            node->last = temp->last;
            temp->last->next = node;
            temp->last = node;
        }
        else if(index < -1)
        {
            temp = list->tail->last;
            for(i = -2; -i <= list->length; --i)
            {
                if(i == index)
                    break;
                temp = temp->last;
            }
            node->last = temp;
            node->next = temp->next;
            temp->next->last = node;
            temp->next = node;
        }
        ++list->length;
    }
}

void dsl_list_remove_at_head(dsl_list_handle_t list, dsl_list_node_handle_t *removed_node)
{
    if(!list) return;
    dsl_list_node_handle_t temp = list->head;
    if(temp)
    {
        list->head = temp->next;
        if(!temp->next)
            list->tail = NULL;
        temp->last = NULL;
        temp->next = NULL;
        --list->length;
    }
    if(removed_node)
        *removed_node = temp;
    else if(temp)
        dsl_list_delete_node(temp);
}

void dsl_list_remove_at_tail(dsl_list_handle_t list, dsl_list_node_handle_t *removed_node)
{
    if(!list) return;
    dsl_list_node_handle_t temp = list->tail;
    if(temp)
    {
        list->tail = temp->last;
        if(!temp->last)
            list->head = NULL;
        temp->last = NULL;
        temp->next = NULL;
        --list->length;
    }
    if(removed_node)
        *removed_node = temp;
    else if(temp)
        dsl_list_delete_node(temp);
}

void dsl_list_remove(dsl_list_handle_t list, int index, dsl_list_node_handle_t *removed_node)
{
    if(!list) return;
    int i = 0;
    dsl_list_node_handle_t temp = NULL;
    if(index == 0 || -index > list->length - 1)
    dsl_list_remove_at_head(list, removed_node);
    else if(index == -1 || index >= list->length - 1)
    dsl_list_remove_at_tail(list, removed_node);
    else
    {
        if(index > 0)
        {
            temp = list->head->next;
            for(i = 1; i < list->length - 1; ++i)
            {
                if(i == index)
                    break;
                temp = temp->next;
            }
            temp->next->last = temp->last;
            temp->last->next = temp->next;
            temp->next = NULL;
            temp->last = NULL;
        }
        else if(index < -1)
        {
            temp = list->tail->last;
            for(i = -2; -i <= list->length - 1; --i)
            {
                if(i == index)
                    break;
                temp = temp->last;
            }
            temp->next->last = temp->last;
            temp->last->next = temp->next;
            temp->next = NULL;
            temp->last = NULL;
        }
        if(removed_node)
            *removed_node = temp;
        else
            dsl_list_delete_node(temp);
        --list->length;
    }
}

dsl_list_node_handle_t dsl_list_add(dsl_list_handle_t list, int index, void *data)
{
    if(!list) return NULL;
    dsl_list_node_handle_t node = dsl_list_create_node(list->data_size);
    if(node)
    {
        if(data)
        dsl_memcpy(node->data, data, list->data_size);
        dsl_list_insert(list, index, node);
        return node;
    }
    return NULL;
}

void dsl_list_delete(dsl_list_handle_t list, int index)
{
    if(!list) return;
    dsl_list_remove(list, index, NULL);
}

dsl_list_node_handle_t dsl_list_modify(dsl_list_handle_t list, int index, void *data)
{
    if(!list || !data) return NULL;
    int i = 0;
    dsl_list_node_handle_t temp = NULL;
    if(index >= 0)
    {
        temp = list->head;
        for(i = 0; i < list->length; ++i)
        {
            if(i == index)
            {
                dsl_memcpy(temp->data, data, list->data_size);
                return temp;
            }
            temp = temp->next;
        }
    }
    else
    {
        temp = list->tail;
        for(i = -1; -i < list->length; --i)
        {
            if(i == index)
            {
                dsl_memcpy(temp->data, data, list->data_size);
                return temp;
            }
            temp = temp->last;
        }
    }
    return NULL;
}

dsl_list_node_handle_t dsl_list_extract(dsl_list_handle_t list, int index, void *data)
{
    if(!list || !data) return NULL;
    int i = 0;
    dsl_list_node_handle_t temp = NULL;
    if(index >= 0)
    {
        temp = list->head;
        for(i = 0; i < list->length; ++i)
        {
            if(i == index)
            {
                dsl_memcpy(data, temp->data, list->data_size);
                return temp;
            }
            temp = temp->next;
        }
    }
    else
    {
        temp = list->tail;
        for(i = -1; -i < list->length; --i)
        {
            if(i == index)
            {
                dsl_memcpy(data, temp->data, list->data_size);
                return temp;
            }
            temp = temp->last;
        }
    }
    return NULL;
}
