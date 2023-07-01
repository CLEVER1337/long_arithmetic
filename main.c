#include "include/big_int.h"
#include "include/list.h"

int main(){
    s_big_int* big_int = big_int_create("77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777");
    s_big_int* big_int2 = big_int_create("666666666666666666666666666666666666666666666666666666666666666666666666666666666666");
    s_big_int val = big_int_sum(*big_int, *big_int2);
    big_int_print(&val);
    //printf("%d", list_find_element(big_int->digits, big_int->digits->size - 1)->value);
}