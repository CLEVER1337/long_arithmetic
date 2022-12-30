#include <stdlib.h>
#include <stddef.h>

typedef struct node{
    int value;
    struct node* next;
}s_node;

s_node* node_create(int value);

typedef struct{
    s_node* head;
    size_t size;
}s_list;

s_list* list_create(int value);

s_node* list_find_element(s_list* list, size_t index);

void list_add_element(s_list* list, int value);

void list_insert_element(s_list* list, int value, size_t index);

void list_change_element(s_list* list, int new_value, size_t index);

void list_delete_element(s_list* list, size_t index);

void list_delete(s_list* list);