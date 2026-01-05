#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header/var_struct.h"
#include "header/operator_function.h"
#include "header/formulas_simplifier.h"
#include "header/reader.h"
#include "header/test.h"



/*******************************************************************************************************************/

void test_diferenciator()
{
    struct tree* TEST_TREE_PARSING[] = 
    {
        NewNode(ADD, OPERATOR, NewNode(0, VARIABLE, NULL, NULL), NewNode(0, VARIABLE, NULL, NULL)),
        NewNode(SUB, OPERATOR, NewNode(0, VARIABLE, NULL, NULL), NewNode(0, VARIABLE, NULL, NULL)),
        NewNode(MUL, OPERATOR, NewNode(0, VARIABLE, NULL, NULL), NewNode(1, VARIABLE, NULL, NULL)),
        NULL
    };
    
    struct tree* TEST_TREE_SIMPLER[] =
    {
        NewNode(2, NUMBER, NULL, NULL),
        NewNode(0, NUMBER, NULL, NULL),
        NewNode(1, VARIABLE, NULL, NULL),
        NULL
    };

    size_t SIZE_TEST = 3;
    char* str_ptr;
    struct data_baze_of_variable* VAR;
    bool PARSING_TEST_MARKER;
    bool SIMPLER_TEST_MARKER;
    int FULL_TEST_MARKER = 0;
    struct tree* root_test_parsing;
    struct tree* root_test_differ;
    struct tree* root_test_simpler;

    FILE* test_file = fopen("test/test.txt", "r");

    if(test_file == NULL)
    {
        perror("TEST FILE OPEN ERROR");
        return;
    }

    size_t count_of_tests = count_lines(test_file);

    rewind(test_file);

    char** TEST_MASSIVE = (char**)calloc(count_of_tests + 1, sizeof(char*));

    char* var_diferr = (char*)calloc(100, sizeof(char));
    
    if (fgets(var_diferr, 100, test_file) != NULL) 
    {
        size_t len = strlen(var_diferr);
        
        while(len > 0 && (var_diferr[len - 1] == '\n' || var_diferr[len - 1] == '\r')) 
        {
            // fprintf(stderr, "here\n");
            var_diferr[len - 1] = '\0';
            len = len - 1;
        }
    }

    // fprintf(stderr, " \'%s\' \n", var_diferr);
    // printf("%zu\n", count_of_tests);

    for(size_t i = 0; i < SIZE_TEST; i++)
    {
        TEST_MASSIVE[i] = (char*)calloc(1024, sizeof(char));
        fgets(TEST_MASSIVE[i], sizeof(TEST_MASSIVE[i]), test_file);
        str_ptr = TEST_MASSIVE[i];
        VAR = init_void_var_struct(20);
        
        root_test_parsing = Parsing(&str_ptr, VAR);

        PARSING_TEST_MARKER = TreeComparison(root_test_parsing, TEST_TREE_PARSING[i]); 

        if(!PARSING_TEST_MARKER)
        {
            fprintf(stdout, RED "FALSE" RESET " PARSING %zu\n", i);
            FULL_TEST_MARKER = FULL_TEST_MARKER + 1;
        }
        else
        {
            fprintf(stdout, GREEN "TRUE" RESET " PARSING %zu\n", i);
        }

        root_test_differ = DiffercationTreeFunction(root_test_parsing, VAR, var_diferr);

        // fprintf(stderr, "sex %f\n", root_test_differ->son1->data);

        // fprintf(stderr, "sex %f\n", root_test_differ->data);

        root_test_simpler = SimplifierTree(root_test_differ);


        SIMPLER_TEST_MARKER = TreeComparison(root_test_simpler, TEST_TREE_SIMPLER[i]); 

        if(!SIMPLER_TEST_MARKER)
        {
            fprintf(stdout, RED "FALSE" RESET " SIMPLER %zu\n", i);
            FULL_TEST_MARKER = FULL_TEST_MARKER + 1;
        }
        else
        {
            fprintf(stdout, GREEN "TRUE" RESET " SIMPLER %zu\n", i);
        }

        free(TEST_MASSIVE[i]);

        TreeDestroy(root_test_parsing);

        TreeDestroy(root_test_differ);

        TreeDestroy(root_test_simpler);

        destroy_var_struct(VAR);
    }

    for(size_t i = 0; i < SIZE_TEST; i++)
    {
        TreeDestroy(TEST_TREE_PARSING[i]);
        TreeDestroy(TEST_TREE_SIMPLER[i]);
    }
    
    fprintf(stdout, "COUNT OF FALSE TESTS:%d\n", FULL_TEST_MARKER);

    free(var_diferr);

    free(TEST_MASSIVE);

    fclose(test_file);
}

/********************************************************************************/

size_t count_lines(FILE* file) 
{   
    size_t line_count = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch == '\n') 
        {
            line_count++;
        }
    }
    
    line_count = line_count;

    return line_count;
}

