#include "list.h"

s_node* node_create(int value){
    s_node* node = malloc(sizeof(s_node));
    node->value = value;
    node->next = NULL;
    return node;
}

s_list* list_create(int value){
    s_list* list = malloc(sizeof(s_list));
    list->head = node_create(value);
    list->size = 1;
    return list;
}

s_node* list_find_element(s_list* list, size_t index){
    if(index >= list->size || index < 0)
        return NULL;

    s_node* ptr = list->head;

    for(size_t i = 0; i < index; i++){
        ptr = ptr->next;
    }

    return ptr;
}

void list_add_element(s_list* list, int value){
    if(list->size == 0){
        list->head = node_create(value);
        list->size = 1;
        return;
    }

    list_find_element(list, list->size - 1)->next = node_create(value);
    list->size++;
}

void list_insert_element(s_list* list, int value, size_t index){
    if(index >= list->size || index < 0)
        return;

    s_node* node = node_create(value);
    node->next = list_find_element(list, index);

    if(index == 0)
        list->head = node;
    else
        list_find_element(list, index - 1)->next = node;

    list->size++;
}

void list_change_element(s_list* list, int new_value, size_t index){
    if(index >= list->size || index < 0)
        return;

    list_find_element(list, index)->value = new_value;
}

void list_delete_element(s_list* list, size_t index){
    if(index >= list->size || index < 0)
        return;

    if(index == 0 && list->size == 1){
        list->head = NULL;
        list->size = 0;
        return;
    }

    s_node* next = list_find_element(list, index + 1);
    free(list_find_element(list, index));

    if(index == 0)
        list->head = next;
    else
        list_find_element(list, index - 1)->next = next;

    list->size--;
}

void list_delete(s_list* list){
    for(int i = (int)list->size - 1; i >= 0; i--){
        list_delete_element(list, i);
    }
    free(list);
}