#include <stdio.h>
#include "header/new_tree.h"
#include "header/operator_function.h"
#include "header/gener_tree_dump.h"
#include "header/latex_dump.h"
#include "header/formulas_simplifier.h"
#include "header/reader.h"




int main()
{
    char stroka[256];
    char var_diferr[100]; 

    fprintf(stdout, "enter line\n");
    fgets(stroka, sizeof(stroka), stdin);

    char* str_ptr = stroka;

    struct data_baze_of_variable* VAR = init_void_var_struct(1);
    struct tree* root = Parsing(&str_ptr, VAR);
    
    fprintf(stdout, "enter var for differincation\n");
    
    scanf("%s", var_diferr);
    
    struct tree* after1 = DiffercationTreeFunction(root, VAR, var_diferr);
    
    struct tree* after = SimplifierTree(after1);
    
    FILE* output_file = fopen("output.txt", "w");
    if (output_file == NULL)
    {
        perror("ERROR FOR OPEN DUMP FILE");
        return -1;
    }

    size_t size = TreePreorder(after, output_file);

    fclose(output_file);

    FILE* dot_file = fopen("dot_file.dot", "w");
    if (dot_file == NULL)
    {
        perror("ERROR FOR OPEN DOT FILE");
        return -1;
    }

    save_tree_to_dot_string(after, dot_file);

    fclose(dot_file);

    FILE* tex_file = fopen("latex_file/dumptex.tex", "w");
    if (!tex_file) 
    {
        printf("ERROR FOPEN FILE\n");
        return -1;
    }

    LatexDump(after, tex_file, VAR);

    fclose(tex_file);

    system("dot -Tpng dot_file.dot -o graph.png");

    system("pdflatex -output-directory=\"latex_file\" dumptex.tex");

    TreeDestroy(root);

    TreeDestroy(after);

    TreeDestroy(after1);

    destroy_var_struct(VAR);

    return (int)size;
}

/***************************************************************************************************************************************/
