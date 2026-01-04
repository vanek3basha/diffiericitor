#include "header/token.h"

struct massive_for_token* token_init(size_t capacity)
{
    struct massive_for_token* token_mas = (struct massive_for_token*)calloc(1, sizeof(struct massive_for_token));
    
    if(token_mas == NULL)
    {
        perror("token is null");
        return NULL;
    }

    token_mas->data = (struct tree**)calloc(capacity, sizeof(struct tree*));
    
    if(token_mas->data == NULL)
    {
        perror("token_mas->data == NULL");
        return NULL;
    }
    
    token_mas->scobka = (size_t*)calloc(capacity, sizeof(size_t));
    
    if(token_mas->scobka == NULL)
    {
        perror("token_mas->scobka == NULL");
        return NULL;
    }

    for(size_t i = 0; i < capacity; i++)
    {
        token_mas->scobka[i] = 0;
    }

    token_mas->size = 0;
    token_mas->capacity = capacity;
    return token_mas;
}

/**********************************************************************************************************************/

void token_push(massive_for_token** token_mas_ptr, struct tree* root, size_t scobka_marker)
{
    // fprintf(stderr, "here_push\n");
    massive_for_token* token_mas = *token_mas_ptr;
    token_mas->data[token_mas->size] = root;
    token_mas->scobka[token_mas->size] = scobka_marker;
    token_mas->size = token_mas->size + 1;
    if(token_mas->size + 3 >= token_mas->capacity)
    {
        *token_mas_ptr = token_realloc(token_mas, token_mas->capacity * 2);
    }
    return;
}

/**********************************************************************************************************************/

void token_destroy(massive_for_token* token_mas)
{
    token_mas->capacity = 0;
    token_mas->size = 0;
    free(token_mas->data);
    free(token_mas->scobka);
    free(token_mas);
}

/**********************************************************************************************************************/

struct massive_for_token* token_realloc(massive_for_token* token_old, size_t new_capacity)
{
    struct massive_for_token* token_mas = (struct massive_for_token*)calloc(1, sizeof(struct massive_for_token));
    
    if(token_mas == NULL)
    {
        perror("token is null");
        return NULL;
    }
    
    token_mas->data = (struct tree**)calloc(new_capacity, sizeof(struct tree*));
    
    if(token_mas->data == NULL)
    {
        perror("token_mas->data == NULL");
        return NULL;
    }
    
    token_mas->scobka = (size_t*)calloc(new_capacity, sizeof(size_t));
    
    if(token_mas->scobka == NULL)
    {
        perror("token_mas->scobka == NULL");
        return NULL;
    }
    
    for(size_t i = 0; i < token_old->capacity; i++)
    {
        token_mas->scobka[i] = token_old->scobka[i];
        token_mas->data[i] = token_old->data[i];
    }
    
    for(size_t i = token_mas->capacity; i < new_capacity; i++)
    {
        token_mas->scobka[i] = 0;
    }
    
    token_mas->size = token_old->size;
    token_mas->capacity = new_capacity;
    
    fprintf(stderr, "realloc\n");
    return token_mas;
}