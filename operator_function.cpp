#include "header/operator_function.h"
#include <string.h>

struct tree* DiffercationTreeFunction(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{    
    if (root->type_node == NUMBER)
    {
        // fprintf(stderr, "tut->\n");
        return ConstDiffercation();
    }
    else if (root->type_node == VARIABLE)
    {
        return VariableDiffercation(root, VAR, var_of_differcation);
    }
    else if (root->type_node == OPERATOR)
    {
        // fprintf(stderr, "in operator tut->\n");
        return OPERATORS_FUNCTION[(int)root->data].pointer(root, VAR, var_of_differcation);
    }
    else 
    {
        return NULL;
    }
}

/*****************************************************************************************************/

struct tree* VariableDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    // fprintf(stderr, "%d root_data- %s  var-%s\n",(int)root->data, VAR->MASSIVE_OF_VARIABLE[(int)root->data], var_of_differcation);
    if(!strcmp(VAR->MASSIVE_OF_VARIABLE[(int)root->data], var_of_differcation))
    {
        return NUM_(1);
    }
    else
    {
        return NUM_(0);
    }
}
/****************************************************************************************************/

struct tree* ConstDiffercation()
{
    return NUM_(0);
}

/****************************************************************************************************/

struct tree* MulDifferication(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return ADD_(MUL_(DERIVATIVE_(root->son1, VAR, var_of_differcation), COPY_(root->son2)), MUL_(DERIVATIVE_(root->son2, VAR, var_of_differcation), COPY_(root->son1)));
}

/****************************************************************************************************/

struct tree* AddDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return ADD_(DERIVATIVE_(root->son1, VAR, var_of_differcation), DERIVATIVE_(root->son2, VAR, var_of_differcation));
}

/****************************************************************************************************/

struct tree* SubDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return SUB_(DERIVATIVE_(root->son1, VAR, var_of_differcation), DERIVATIVE_(root->son2, VAR, var_of_differcation));
}

/****************************************************************************************************/

struct tree* DifDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return DIF_(SUB_(MUL_(DERIVATIVE_(root->son1, VAR, var_of_differcation), COPY_(root->son2)), MUL_(DERIVATIVE_(root->son2, VAR, var_of_differcation), COPY_(root->son1))), POW_(COPY_(root->son2), NUM_(2)));
}

/****************************************************************************************************/

struct tree* PowDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return MUL_(POW_(COPY_(root->son1), COPY_(root->son2)), ADD_(MUL_(DERIVATIVE_(root->son2, VAR, var_of_differcation), LOG_(EXP, COPY_(root->son1))), MUL_(DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), COPY_(root->son1)), COPY_(root->son2))));
}

/****************************************************************************************************/

struct tree* LogDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return DIF_( \
                SUB_( \
                    MUL_( \
                        DIF_( \
                            DERIVATIVE_(root->son2, VAR, var_of_differcation), \
                            COPY_(root->son2)), \
                        LOG_(
                            EXP, \
                            COPY_(root->son1))), \
                    MUL_( \
                        DIF_( \
                            DERIVATIVE_(root->son1, VAR, var_of_differcation), \
                            COPY_(root->son1)), \
                        LOG_(
                            EXP, \
                            COPY_(root->son2)))),\
                POW_( \
                    LOG_( \
                        EXP, \
                        COPY_(root->son1)), \
                    NUM_(2)));
}

/****************************************************************************************************/

struct tree* SinDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return MUL_(DERIVATIVE_(root->son1, VAR, var_of_differcation), COS_(COPY_(root->son1)));
}

/****************************************************************************************************/

struct tree* CosDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return MUL_(DERIVATIVE_(root->son1, VAR, var_of_differcation), SUB_(NUM_(0), SIN_(COPY_(root->son1))));
}

/****************************************************************************************************/

struct tree* TanDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), POW_(COS_(root->son1), NUM_(2)));
}

/****************************************************************************************************/

struct tree* CtgDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return SUB_(NUM_(0) , DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), POW_(SIN_(COPY_(root->son1)), NUM_(2))));
}

/****************************************************************************************************/

struct tree* ArcsinDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), POW_(SUB_(NUM_(1), POW_(COPY_(root->son1), NUM_(2))), NUM_(0.5)));
}

/****************************************************************************************************/

struct tree* ArccosDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return SUB_(NUM_(0), DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), POW_(SUB_(NUM_(1), POW_(COPY_(root->son1), NUM_(2))), NUM_(0.5))));
}

/****************************************************************************************************/

struct tree* ArctanDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), ADD_(NUM_(1), POW_(COPY_(root->son1), NUM_(2))));
}

/****************************************************************************************************/

struct tree* ArcctgDiffercation(struct tree* root, struct data_baze_of_variable* VAR, char* var_of_differcation)
{
    return SUB_(NUM_(0), DIF_(DERIVATIVE_(root->son1, VAR, var_of_differcation), ADD_(NUM_(1), POW_(COPY_(root->son1), NUM_(2)))));
}