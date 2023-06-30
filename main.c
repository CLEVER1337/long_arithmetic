#include "include/big_int.h"
#include "include/list.h"

int main(){
    s_big_int* big_int = big_int_create("00133700");
    s_big_int* big_int2 = big_int_create("1337000000000000000000000");
    big_int_is_less(*big_int, *big_int2) ? printf("Yes\n") : printf("No\n");
    s_big_int val = big_int_opposite_value(*big_int2);
    big_int_print(&val);
    //printf("%d", list_find_element(big_int->digits, big_int->digits->size - 1)->value);
}