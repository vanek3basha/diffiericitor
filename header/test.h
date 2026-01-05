#ifndef TEST_H_
#define TEST_H_

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

#include "new_tree.h"

void test_diferenciator();

size_t count_lines(FILE* file);

// static const struct tree* TEST_TREE_PARSING[] = 
// {
//     &(tree){2 , 1, NULL, NULL},
//     NULL
// };

// static const struct tree* TEST_TREE_SIMPLER[] = 
// {
//     &(tree){2, 1, NULL, NULL},
//     NULL
// };

#endif