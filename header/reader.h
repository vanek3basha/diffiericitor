#ifndef _READER_H_
#define _READER_H_

#include "new_tree.h"
#include "token.h"
#include "operator_function.h"
#include "var_struct.h"

#define CreateOperatorNode(NUM) NewNode(NUM, OPERATOR, NULL, NULL)
#define CreateNumberNode(NUM) NewNode(NUM, NUMBER, NULL, NULL)
#define CreateVariableNode(var_num) NewNode(var_num, VARIABLE, NULL, NULL)

void skip_spaces(char** expression);
int isoperator(char* expression);
struct tree* Parsing(char** expression, struct data_baze_of_variable* VAR);
struct tree* SborkaLineynogoVirazzheniya(massive_for_token* tok);
struct tree* ParsingNumber(char** expression);
struct tree* ParsingVariable(char** expression, struct data_baze_of_variable* VAR);
struct tree* ParsingSkobka(char** expression, struct data_baze_of_variable* VAR);
struct tree* ParsingOperator(char** expression, struct data_baze_of_variable* VAR);


struct INF_OF_OPERATOR
{
    OPERATORS num;
    const char* name;
    int priority;
    int arity;
    size_t count_of_simbol;
};

const INF_OF_OPERATOR date_baza_operators[] =
{
    {ADD, "+", 1, 2, 1},
    {SUB, "-", 1, 2, 1},
    {MUL, "*", 2, 2, 1},
    {DIF, "/", 2, 2, 1},
    {POW, "^", 3, 2, 1},
    {LOG, "log", 4, 1, 3},
    {SIN, "sin", 4, 1, 3},
    {COS, "cos", 4, 1, 3},
    {TAN, "tan", 4, 1, 3},
    {CTG, "ctg", 4, 1, 3},
    {ARCSIN, "arcsin", 4, 1, 6},
    {ARCCOS, "arccos", 4, 1, 6},
    {ARCTAN, "arctan", 4, 1, 6},
    {ARCCTG, "arcctg", 4, 1, 6},
    {NONE, NULL, 0, 0, 0}
};

#endif