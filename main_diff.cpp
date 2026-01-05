#include <stdio.h>
#include "header/new_tree.h"
#include "header/operator_function.h"
#include "header/gener_tree_dump.h"
#include "header/latex_dump.h"
#include "header/formulas_simplifier.h"
#include "header/reader.h"
#include "header/test.h"

int main(int argc, char* argv[])
{
    if(argc < 2) 
    {
        perror("argc < 2\n");
        return -1;
    }
    char* filename = argv[1];
    
    char stroka[256];
    char var_diferr[100]; 

    if(!strcmp(filename, "test"))
    {
        test_diferenciator();
        // fprintf(stdout, "Want you continue?(0 - continue, another - don\'t continue\n");
        // int CONTINUE_MARKER;
        // fscanf(stdin, "%d", &CONTINUE_MARKER);
        // if(CONTINUE_MARKER)
        // {
            return 0;
        // }
    }
    if(!strcmp(filename, "stdin"))
    {
        fprintf(stdout, "enter line\n");

        fgets(stroka, sizeof(stroka), stdin);

        fprintf(stdout, "enter var for differincation\n");

        fscanf(stdin, "%s", var_diferr);
    }
    else
    {
        FILE* input_file = fopen(filename, "r");
        if(input_file == NULL)
        {
            perror("input_file - NULL\n");
            return -1;
        }

        fgets(stroka, sizeof(stroka), input_file);
        
        
        fscanf(input_file, "%s", var_diferr);

        fclose(input_file);
    }

    char* str_ptr = stroka;

    struct data_baze_of_variable* VAR = init_void_var_struct(1);
    
    struct tree* root_parsing = Parsing(&str_ptr, VAR);
    
    struct tree* root_differ = DiffercationTreeFunction(root_parsing, VAR, var_diferr);
    
    struct tree* root_simpler = SimplifierTree(root_differ);
    
    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL)
    {
        perror("ERROR FOR OPEN DUMP FILE");
        return -1;
    }

    size_t size = TreePreorder(root_simpler, output_file);

    fclose(output_file);

    FILE* dot_file = fopen("dot_file/dot_file.dot", "w");
    if (dot_file == NULL)
    {
        perror("ERROR FOR OPEN DOT FILE");
        return -1;
    }

    save_tree_to_dot_string(root_simpler, dot_file);

    fclose(dot_file);

    FILE* tex_file = fopen("latex_file/dumptex.tex", "w");
    if (!tex_file) 
    {
        printf("ERROR FOPEN FILE\n");
        return -1;
    }

    LatexDump(root_simpler, tex_file, VAR);

    fclose(tex_file);

    system("dot -Tpng dot_file/dot_file.dot -o dot_file/graph.png");

    system("pdflatex -output-directory=\"latex_file\" dumptex.tex");

    TreeDestroy(root_parsing);

    TreeDestroy(root_differ);

    TreeDestroy(root_simpler);

    destroy_var_struct(VAR);

    return (int)size;
}

/***************************************************************************************************************************************/
