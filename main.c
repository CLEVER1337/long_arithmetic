#include "include/big_int.h"
#include "include/list.h"

int main(){
    s_big_int* big_int = big_int_create("12345678901234567890");
    big_int_print(big_int);
}