#ifndef VAR_STRUCT_H
#define VAR_STRUCT_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct data_baze_of_variable 
{
    char** MASSIVE_OF_VARIABLE;
    size_t count_of_variable;
    size_t capacity;
};

struct data_baze_of_variable* init_void_var_struct(size_t capacity);
void destroy_var_struct(struct data_baze_of_variable* VAR);
struct data_baze_of_variable* var_struct_realloc(struct data_baze_of_variable* VAR_OLD, size_t new_capacity);

#endif