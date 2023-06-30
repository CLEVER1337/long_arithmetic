#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct big_int{
    int base;

    s_list* digits;

    bool is_negative;
    bool is_zero;
}s_big_int;

void big_int_delete_leadings_zero(s_big_int* big_int);

void big_int_print(s_big_int* big_int);

s_big_int* big_int_create(char* value);

void big_int_delete(s_big_int* big_int);

s_big_int big_int_opposite_value(s_big_int big_int);

bool big_int_is_equal(s_big_int first, s_big_int second);

bool big_int_is_less(s_big_int first, s_big_int second);

#endif