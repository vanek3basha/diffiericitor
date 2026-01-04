#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "new_tree.h"
#include <stdlib.h>

struct massive_for_token
{
    struct tree** data;
    size_t* scobka;
    size_t capacity;
    size_t size;
};

struct massive_for_token* token_init(size_t capacity);
void token_push(massive_for_token** token_mas, struct tree* root, size_t scobka_marker);
struct massive_for_token* token_realloc(massive_for_token* token_old, size_t new_capacity);
void token_destroy(massive_for_token* token_mas);

#endif