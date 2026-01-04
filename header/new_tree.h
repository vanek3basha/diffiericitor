#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>

// static const struct
// {
//     const char* operator_stroka;
//     size_t count_of_simbol;
//     size_t num_of_operator;
// } CHITALKA_FOR_OPERATOR[] = {
//     {"\0", 1, 0},
//     {"+", 1, 1},
//     {"-", 1, 2},
//     {"*", 1, 3},
//     {"/", 1, 4},
//     {"^", 1, 5},
//     {"log", 3, 6},
//     {"sin", 3, 7},
//     {"cos", 3, 8},
//     {"tan", 3, 9},
//     {"ctg", 3, 10},
//     {"arcsin", 6, 11},
//     {"arccos", 6, 12},
//     {"arctan", 6, 13},
//     {"arcctg", 6, 14}
// };

static const char* const operators_massive[] = {
    "0",
    "+",
    "-",
    "*",
    "/",
    "^",
    "log",
    "sin",
    "cos",
    "tan",
    "ctg",
    "arcsin",
    "arccos",
    "arctan",
    "arcctg"
};

static const int NUM_OF_OPERATORS = sizeof(operators_massive) / sizeof(operators_massive[0]);

static const char* const variable_massive[] = {
    "0",
    "x",
    "y",
    "z"
};

static const int NUM_OF_VARIABLE = sizeof(variable_massive) / sizeof(operators_massive[0]);


typedef size_t node_of_tree_type;
typedef double data_type;

struct tree 
{
    data_type data;
    node_of_tree_type type_node;
    struct tree* son1;
    struct tree* son2;
};

enum NODETYPE{
    NUMBER =  1,
    OPERATOR = 2,
    VARIABLE = 3
};

struct tree* NewNode(data_type data_n, node_of_tree_type type_node_n, struct tree* son1_n, struct tree* son2_n);

struct tree* NewNodeWithOutCopy(data_type data_n, node_of_tree_type type_node_n, struct tree* son1_n, struct tree* son2_n);

size_t TreePreorder(struct tree* root, FILE* dump_file);

struct tree* CopyTreeFunction(struct tree* root);

struct tree* ReadTreeFunction(FILE* read_file);

struct tree* ReadRoot(char* buffer, size_t size_buffer);

size_t TreeDestroy(struct tree* root);

#endif