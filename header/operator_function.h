#ifndef _OPERATORS_
#define _OPERATORS_

#include "new_tree.h"
#include "var_struct.h"
#include <math.h>

enum OPERATORS{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIF = 4,
    POW = 5,
    LOG = 6,
    SIN = 7,
    COS = 8,
    TAN = 9,
    CTG = 10,
    ARCSIN = 11,
    ARCCOS = 12,
    ARCTAN = 13,
    ARCCTG = 14,
    NONE = 100
};

struct tree* ConstDiffercation();

struct tree* VariableDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* MulDifferication(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* AddDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* SubDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* DifDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* PowDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* LogDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* DiffercationTreeFunction(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* SinDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* CosDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* TanDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* CtgDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* ArcsinDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* ArccosDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* ArctanDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

struct tree* ArcctgDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation);

static const struct 
{
    int operators_number;
    tree* (*pointer)(tree*, data_baze_of_variable*, char*);
} OPERATORS_FUNCTION [] = {
    {0, NULL},
    {1, AddDiffercation},
    {2, SubDiffercation},
    {3, MulDifferication},
    {4, DifDiffercation},
    {5, PowDiffercation},
    {6, LogDiffercation},
    {7, SinDiffercation},
    {8, CosDiffercation},
    {9, TanDiffercation},
    {10, CtgDiffercation},
    {11, ArcsinDiffercation},
    {12, ArccosDiffercation},
    {13, ArctanDiffercation},
    {14, ArcctgDiffercation},
    {31, VariableDiffercation}
};

const double expanenta = exp(1.00);
// static const int OPERATORS_COUNT = sizeof(OPERATORS_FUNCTION) / sizeof(OPERATORS_FUNCTION[0]);

#define ADD_(son1, son2) NewNode(ADD, OPERATOR, son1, son2)
#define MUL_(son1, son2) NewNode(MUL, OPERATOR, son1, son2)
#define SUB_(son1, son2) NewNode(SUB, OPERATOR, son1, son2)
#define DIF_(son1, son2) NewNode(DIF, OPERATOR, son1, son2)
#define POW_(son1, son2) NewNode(POW, OPERATOR, son1, son2)
#define LOG_(son1, son2) NewNode(LOG, OPERATOR, son1, son2)
#define COS_(son1)       NewNode(COS, OPERATOR, son1, NULL)
#define SIN_(son1)       NewNode(SIN, OPERATOR, son1, NULL)
#define TAN_(son1)       NewNode(TAN, OPERATOR, son1, NULL)
#define CTG_(son1)       NewNode(CTG, OPERATOR, son1, NULL) 
#define NUM_(number)     NewNode(number, NUMBER, NULL, NULL)
#define EXP              NewNode(expanenta, NUMBER, NULL, NULL) 
#define COPY_(root)      CopyTreeFunction(root)
#define DERIVATIVE_(root, VAR, x) DiffercationTreeFunction(root, VAR, x)
#define ARCSIN_(son1)    NewNode(ARCSIN, OPERATOR, son1, NULL)
#define ARCCOS_(son1)    NewNode(ARCCOS, OPERATOR, son1, NULL)
#define ARCTAN_(son1)    NewNode(ARCTAN, OPERATOR, son1, NULL)
#define ARCCTG_(son1)    NewNode(ARCCTG, OPERATOR, son1, NULL)

#endif