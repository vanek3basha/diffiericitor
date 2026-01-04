#include "header/latex_dump.h"
#include "header/formulas_simplifier.h"


int LatexDump(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{    
    fprintf(tex_file, "\\documentclass{article}\n");
    fprintf(tex_file, "\\usepackage{amsmath}\n");
    fprintf(tex_file, "\\begin{document}\n$$");
    TEXprintf_function(root, tex_file, VAR);
    fprintf(tex_file, "$$\n\\end{document}\n");
    
    return 1;
}

/**********************************************************************************************************************/

int TEXprintf_function(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    if (root->type_node == NUMBER)
    {
        ConstTEX(root, tex_file);
        return 1;
    }
    else if (root->type_node == VARIABLE)
    {
        VariableTEX(root, tex_file, VAR);
        return 3;
    }
    else if (root->type_node == OPERATOR)
    {
        return LATEX_FUNCTION[(int)root->data].pointer(root, tex_file, VAR);
    }
    else 
    {
        perror("PIZDEC KAKOY TO SLUCHILSYA BRAT");
        return -1;
    }
}


/************************************************************************************************************/

int AddTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    TEXprintf_function(root->son1, tex_file, VAR);
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }

    fprintf(tex_file, " + ");
    
    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    TEXprintf_function(root->son2, tex_file, VAR);
    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }
    return 2;
}

/************************************************************************************************************/

int SubTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    if(root->son1->type_node != NUMBER || !iszero(root->son1->data))
    {
        TEXprintf_function(root->son1, tex_file, VAR);
    }
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }
    
    fprintf(tex_file, " - ");

    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    TEXprintf_function(root->son2, tex_file, VAR);
    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }
    return 2;
}

/************************************************************************************************************/

int MulTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    TEXprintf_function(root->son1, tex_file, VAR);
    if(root->son1->son1 != NULL && root->son1->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }

    fprintf(tex_file, " * ");

    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, "(");
    }
    TEXprintf_function(root->son2, tex_file, VAR);
    if(root->son2->son1 != NULL && root->son2->son2 != NULL)
    {
        fprintf(tex_file, ")");
    }
    return 2;
}

/************************************************************************************************************/

int DifTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\frac{");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, "}{");
    TEXprintf_function(root->son2, tex_file, VAR);
    fprintf(tex_file, "}");
    return 2;
}

/************************************************************************************************************/

int PowTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ") ^ {");
    TEXprintf_function(root->son2, tex_file, VAR);
    fprintf(tex_file, "}");
    return 2;
}

/************************************************************************************************************/

int LogTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\log_{");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, "} (");
    TEXprintf_function(root->son2, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int SinTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\sin(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int CosTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\cos(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int TanTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\tan(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int CtgTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\cot(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int ArcsinTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\arcsin(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int ArccosTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\arccos(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int ArctanTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\arctan(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int ArcctgTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "\\arccot(");
    TEXprintf_function(root->son1, tex_file, VAR);
    fprintf(tex_file, ")");
    return 2;
}

/************************************************************************************************************/

int ConstTEX(struct tree* root, FILE* tex_file)
{
    fprintf(tex_file, "%f", root->data);
    return 1;
}

/************************************************************************************************************/

int VariableTEX(struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR)
{
    fprintf(tex_file, "%s", VAR->MASSIVE_OF_VARIABLE[(int)root->data]);
    return 3;
}