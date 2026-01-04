#ifndef _LATEX_
#define _LATEX_

#include "new_tree.h"
#include "var_struct.h"

int LatexDump          (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int TEXprintf_function (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int AddTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int SubTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int MulTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int DifTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int PowTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int LogTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int SinTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int CosTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int TanTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int CtgTEX             (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int ArcsinTEX          (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int ArccosTEX          (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int ArctanTEX          (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int ArcctgTEX          (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

int ConstTEX           (struct tree* root, FILE* tex_file);

int VariableTEX        (struct tree* root, FILE* tex_file, struct data_baze_of_variable* VAR);

static const struct
{
    int latex_operators_number;
    int (*pointer)(tree*, FILE*, struct data_baze_of_variable*);
} LATEX_FUNCTION [] = {
    {0, NULL},
    {1, AddTEX},
    {2, SubTEX},
    {3, MulTEX},
    {4, DifTEX},
    {5, PowTEX},
    {6, LogTEX},
    {7, SinTEX},
    {8, CosTEX},
    {9, TanTEX},
    {10, CtgTEX},
    {11, ArcsinTEX},
    {12, ArccosTEX},
    {13, ArctanTEX},
    {14, ArcctgTEX},
    {31, VariableTEX}
};

#endif