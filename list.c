#include "list.h"
#include <stdlib.h>
#include <stdio.h>

node_t *f_node_constructor(void *content)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->content = content;
    return new_node;
}

void f_node_destructor(node_t *node)
{
    free(node->content);
    free(node);
}

list_t *f_list_constructor()
{
    list_t* new_list = (list_t*)malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    return new_list;
}

void f_list_destructor(list_t* list)
{
    if (list->size > 0)
    {
        node_t* node_to_free = list->head;
        for (int i = 1; i < list->size; i++)
        {
            node_to_free = node_to_free->next;
            f_node_destructor(node_to_free->prev);
        }
        f_node_destructor(node_to_free);
    }
    free(list);
}

void f_list_insert(list_t *list, void *content, unsigned int index)
{
    if (index > list->size)
    {
        printf("Index %d out of bounds for list at %p", index, list);
        return;
    }
    
    if (index == list->size)
    {
        f_list_insert_back(list, content);
        return;
    }

    if (index == 0)
    {
        f_list_insert_front(list, content);
        return;
    }

    node_t* node_before = list->head;
    for (int i = 0; i < index; i++)
    {
        node_before = node_before->next;
    }
    f_list_insert_after(list, content, node_before);
    list->size += 1;
    return;
}

void f_list_insert_front(list_t *list, void *content)
{
    node_t* new_head = f_node_constructor(content);
    if (list->size == 0)
    {
        list->head = new_head;
        list->tail = new_head;
        list->size += 1;
        return;
    }
    new_head->next = list->head;
    list->head->prev = new_head;
    list->head = new_head;
    list->size += 1;
    return;
}


void f_list_insert_back(list_t *list, void *content)
{
    node_t* new_tail = f_node_constructor(content);
    if (list->size == 0)
    {
        list->head = new_tail;
        list->tail = new_tail;
        list->size += 1;
        return;
    }
    new_tail->prev = list->tail;
    list->tail->next = new_tail;
    list->tail = new_tail;    
    list->size += 1;
    return;
}

void f_list_insert_after(list_t *list, void *content, node_t *node)
{
    if (list->tail == node)
    {
        f_list_insert_back(list, content);
        return;
    }

    node_t* new_node = f_node_constructor(content);
    new_node->prev = node;
    new_node->next = node->next;
    node->next->prev = new_node;
    node->next = new_node;
    list->size += 1;
    return;
}

void f_list_insert_before(list_t *list, void *content, node_t *node)
{
    if (list->head == node)
    {
        f_list_insert_front(list, content);
        return;
    }

    node_t* new_node = f_node_constructor(content);
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
    list->size += 1;
    return;
}

void f_list_remove(list_t *list, node_t *node)
{
    if (list->head == node && list->tail == node)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else if (list->head == node)
    {
        list->head = node->next;
        list->head->next = NULL;
    }
    else if (list->tail == node)
    {
        list->tail = node->prev;
        list->tail->next = NULL;
    }
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    f_node_destructor(node);
    list->size -= 1;
    return;
}
