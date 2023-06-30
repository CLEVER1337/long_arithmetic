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

void big_int_delete(s_big_int* big_int){
    list_delete(big_int->digits);
    free(big_int);
}

s_big_int big_int_opposite_value(s_big_int big_int){
    big_int.is_negative = !big_int.is_negative;
    return big_int;
}

bool big_int_is_equal(s_big_int first, s_big_int second){
    if(first.is_negative != second.is_negative)
        return false;

    if(first.digits->size != second.digits->size)
        return false;

    for(size_t i = 0; i < first.digits->size; i++)
        if(list_find_element(first.digits, i)->value != list_find_element(second.digits, i)->value)
            return false;

    return true;
}

bool big_int_is_less(s_big_int first, s_big_int second){
    if(big_int_is_equal(first, second)) return false;

    if(first.is_negative){
        if(second.is_negative) 
            return big_int_is_less(big_int_opposite_value(first), big_int_opposite_value(second));
        else 
            return true;
    }
    else if(second.is_negative){
        return false;
    }
    else{
        if(first.digits->size != second.digits->size){
            return first.digits->size < second.digits->size;
        }
        else{
            for(size_t i = first.digits->size - 1; i >= 0; i--){
                if(list_find_element(first.digits, i)->value != list_find_element(second.digits, i)->value) 
                    return list_find_element(first.digits, i)->value < list_find_element(second.digits, i)->value;
                
                return false;
            }
        }
    }
}