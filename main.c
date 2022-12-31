#include "include/big_int.h"
#include "include/list.h"

int main(){
    s_big_int* big_int = big_int_create("133713371337133713371337");
    big_int_print(big_int);
    //printf("%d", list_find_element(big_int->digits, big_int->digits->size - 1)->value);
}