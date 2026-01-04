#include "header/var_struct.h"
#include <stdio.h>

struct data_baze_of_variable* init_void_var_struct(size_t capacity)
{
    struct data_baze_of_variable* VAR = (struct data_baze_of_variable*)calloc(1, sizeof(struct data_baze_of_variable));

    if(VAR == NULL)
    {
        perror("var_struct calloc ERROR\n");
        return NULL;
    }

    VAR->MASSIVE_OF_VARIABLE = (char**)calloc(capacity, sizeof(char*));
    
    if(VAR->MASSIVE_OF_VARIABLE == NULL)
    {
        perror("var_struct massive calloc ERROR\n");
        return NULL;
    }

    VAR->count_of_variable = 0;
    VAR->capacity = capacity;
    return VAR;
}

/**********************************************************************************************************************/

void destroy_var_struct(struct data_baze_of_variable* VAR)
{
    for(size_t i = 0; i < VAR->count_of_variable; i++)
    {
        free(VAR->MASSIVE_OF_VARIABLE[i]);
    }
    VAR->count_of_variable = 0;
    VAR->capacity = 0;
    free(VAR->MASSIVE_OF_VARIABLE);
    free(VAR);
}

/**********************************************************************************************************************/

struct data_baze_of_variable* var_struct_realloc(struct data_baze_of_variable* VAR, size_t new_capacity)
{
    // struct data_baze_of_variable* VAR = (struct data_baze_of_variable*)calloc(1, sizeof(struct data_baze_of_variable));

    if(VAR == NULL)
    {
        perror("var_struct calloc ERROR\n");
        return NULL;
    }

    char** new_massive = (char**)realloc(VAR->MASSIVE_OF_VARIABLE, new_capacity * sizeof(char*));

    if(new_massive == NULL)
    {
        perror("new_massive calloc ERROR\n");
        return NULL;
    }

    VAR->MASSIVE_OF_VARIABLE = new_massive;

    for(size_t i = VAR->capacity; i < new_capacity; i++)
    {
        VAR->MASSIVE_OF_VARIABLE[i] = NULL;
    }

    VAR->capacity = new_capacity;

    return VAR;
    
}