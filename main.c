#include "include/big_int.h"
#include "include/list.h"

int main(){
    s_big_int* big_int = big_int_create("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    s_big_int* big_int2 = big_int_create("6");
    //s_big_int val = big_int_sub(*big_int, *big_int2);
    //big_int_increment(big_int);
    s_big_int var = big_int_mul(*big_int, *big_int2);
    big_int_print(&var);
    //printf("%d", list_find_element(big_int->digits, big_int->digits->size - 1)->value);
}
