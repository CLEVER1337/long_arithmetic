#include "big_int.h"

void big_int_delete_leadings_zero(s_big_int* big_int){
    while(big_int->digits->size > 0 && list_find_element(big_int->digits, big_int->digits->size - 1)->value == 0)
        list_delete_element(big_int->digits, big_int->digits->size - 1);
    if(big_int->digits->size == 0) big_int->is_zero = true;
    if(big_int->is_zero) big_int->is_negative = false;
}

void big_int_print(s_big_int* big_int){
    if(big_int->is_zero){
        printf("0");
        return;
    }
    if(big_int->is_negative)
        printf("-");
    printf("%d", list_find_element(big_int->digits, big_int->digits->size - 1)->value);
    for(int i = (int)big_int->digits->size - 2; i >= 0; --i)
        printf("%09d", list_find_element(big_int->digits, i)->value);
}

s_big_int* big_int_create(char* value){
    s_big_int* big_int = malloc(sizeof(s_big_int));

    big_int->digits = list_create(0);
    list_delete_element(big_int->digits, 0);

    big_int->base = 1000000000;

    if(strlen(value) == 0){
        big_int->is_negative = false;
        big_int->is_zero = true;
    }
    else{
        big_int->is_zero = false;

        if(value[0] == '-'){
            big_int->is_negative = true;
            value = value + 1;
        }
        else{
            big_int->is_negative = false;
        }

        for(int i = (int)strlen(value); i > 0; i -= 9){
            char substr[10];
            if(i < 9){
                strncpy(substr, value, i);
                substr[i] = '\0';
            }
            else{
                strncpy(substr, value + i - 9, 9);
                substr[9] = '\0';
            }
            list_add_element(big_int->digits, atoi(substr));
        }

        big_int_delete_leadings_zero(big_int);
    }
    return big_int;
}

void big_int_delete(s_big_int* big_int);