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

bool big_int_is_not_equal(s_big_int first, s_big_int second){
    return !big_int_is_equal(first, second);
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

bool big_int_is_bigger(s_big_int first, s_big_int second){
    return !big_int_is_less_or_equal(first, second);
}

bool big_int_is_less_or_equal(s_big_int first, s_big_int second){
    return big_int_is_less(first, second) || big_int_is_equal(first, second);
}

bool big_int_is_bigger_or_equal(s_big_int first, s_big_int second){
    return !big_int_is_less(first, second);
}

s_big_int big_int_sum(s_big_int first, s_big_int second){
    if(first.is_negative){
        if(second.is_negative)
            return big_int_opposite_value(big_int_sum(big_int_opposite_value(first), big_int_opposite_value(second)));
        else
            return big_int_sub(second, big_int_opposite_value(first));
    }
    else if(second.is_negative)
        return big_int_sub(first, big_int_opposite_value(second));
    
    int carry = 0;
    int stop = MAX(first.digits->size, second.digits->size);
    for(size_t i = 0; i < stop || carry != 0; i++){
        if(i == first.digits->size) list_add_element(first.digits, 0);
        list_find_element(first.digits, i)->value += carry + (i < second.digits->size ? list_find_element(second.digits, i)->value : 0);
        carry = (list_find_element(first.digits, i)->value >= first.base);
        if(carry != 0) list_find_element(first.digits, i)->value -= first.base;
    }

    return first;
}

s_big_int big_int_sub(s_big_int first, s_big_int second){
    if(second.is_negative) return big_int_sum(first, big_int_opposite_value(second));
    else if(first.is_negative) return big_int_opposite_value(big_int_sum(big_int_opposite_value(first), second));
    else if(big_int_is_less(first, second)) return big_int_opposite_value(big_int_sub(second, first));
    
    int carry = 0;
    for(size_t i = 0; i < second.digits->size || carry != 0; i++){
        list_find_element(first.digits, i)->value -= carry + (i < second.digits->size ? list_find_element(second.digits, i)->value : 0);
        carry = (list_find_element(first.digits, i)->value < 0);
        if(carry != 0) list_find_element(first.digits, i)->value += first.base;
    }

    big_int_delete_leadings_zero(&first);

    return first;
}

void big_int_increment(s_big_int* big_int){
    *big_int = (big_int_sum(*big_int, *big_int_create("1")));
}

void big_int_decrement(s_big_int* big_int){
    *big_int = (big_int_sub(*big_int, *big_int_create("1")));
}

s_big_int big_int_mul(s_big_int first, s_big_int second){
    s_big_int* result = big_int_create("0");
    
    list_resize(result->digits, first.digits->size + second.digits->size);
    
    for(size_t i = 0; i < first.digits->size; i++){
        int carry = 0;
        for(size_t j = 0; j < second.digits->size || carry != 0; ++j){
            long long current = list_find_element(result->digits, i + j)->value +
                                list_find_element(first.digits, i)->value * 1LL * 
                                (j < second.digits->size ? list_find_element(second.digits, j)->value : 0) +
                                carry;
            
            list_find_element(result->digits, i + j)->value = current % result->base;
            carry = current / result->base;
        }
    }
    
    result->is_negative = first.is_negative != second.is_negative;
    result->is_zero = false;
    big_int_delete_leadings_zero(result);
    return *result;
}
