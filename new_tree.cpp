#include <string.h>
#include "header/new_tree.h"
#include "header/operator_function.h"

/********************************************************************************************************************/

struct tree* NewNode(data_type data_n, node_of_tree_type type_node_n, struct tree* son1_n, struct tree* son2_n)
{
    struct tree* new_son = (struct tree*)calloc(1, sizeof(struct tree));
    
    if(new_son == NULL)
    {
        perror("ERROR NEW_SON CALLOC");
        return NULL;
    }

    new_son->son1 = son1_n;
    new_son->son2 = son2_n;
    new_son->data = data_n;
    new_son->type_node = type_node_n;

    return new_son;
}

/********************************************************************************************************************/

size_t TreePreorder(struct tree* root, FILE* dump_file)
{
    size_t size = 1;

    fprintf(dump_file, " (");

    switch(root->type_node)
    {
        case NUMBER:
            fprintf(dump_file, "\"%lf\"", root->data);
            break;

        case OPERATOR:
            fprintf(dump_file, "\"%s\"", operators_massive[(int)root->data]);
            break;

        case VARIABLE:
            fprintf(dump_file, "\"%s\"", variable_massive[(int)root->data]);
            break;

        default:
            fprintf(stderr, "Undeclarated type");
            break;
    }

    if(root->son1 != NULL)
    { 
        size = size + TreePreorder(root->son1, dump_file);
    }
    else
    {
        fprintf(dump_file, " (nil)");
    }

    if(root->son2 != NULL)
    {
        size = size + TreePreorder(root->son2, dump_file);
    }
    else
    {
        fprintf(dump_file, " (nil)");
    }

    fprintf(dump_file, ")");

    return size;
}

/******************************************************************************************************************/

struct tree* CopyTreeFunction(struct tree* root)
{
    if(root == NULL)
    {
        return NULL;
    }

    struct tree* new_node = NewNode(root->data, root->type_node, CopyTreeFunction(root->son1), CopyTreeFunction(root->son2));

    if(new_node == NULL)
    {
        perror("ERROR IN CALLOC NEW POINT");
    }

    // TreeDestroy(root);
    
    return new_node;
}

/*******************************************************************************************************************/

struct tree* ReadTreeFunction(FILE* read_file)
{
    size_t size_buffer = 2000;

    char* buffer = (char*)calloc(size_buffer, sizeof(char));

    if(fgets(buffer, (int)size_buffer, read_file) == NULL)
    {
        perror("ERROR FOR READ FILE: fgets return NULL");
        return {};
    }

    struct tree* root = ReadRoot(buffer, size_buffer);
    
    free(buffer);

    if(root == NULL)
    {
        
        perror("ERROR FOR READ FILE: root - NULL");
        return NULL;
    }

    else
    {
        return root;
    }

}
/*********************************************************************************************************/

struct tree* ReadRoot(char* buffer, size_t size_buffer)
{
    if(!strncmp(" (nil)", buffer, 6))
    {
        return NULL;
    }

    struct tree* root = (struct tree*)calloc(1, sizeof(struct tree));

    size_t start_root_data = (size_t)(strchr(buffer, '\"') - buffer + 1);

    size_t end_root_data = (size_t)(strchr(buffer + start_root_data, '\"') - buffer);

    char* temp_buffer = (char*) calloc(size_buffer, sizeof(char));
    
    temp_buffer = strcpy(temp_buffer, buffer + start_root_data);
    
    temp_buffer[end_root_data - start_root_data] = '\0';


    int MARKER = 0;

    for (size_t i = 0; i < NUM_OF_OPERATORS; i++)
    {
        if(!strcmp(temp_buffer, operators_massive[i]))
        {
            root->data = (double)i;
            root->type_node = 2;
            MARKER = 1;
            break;
        }
    }

    for (size_t i = 0; i < NUM_OF_VARIABLE; i++)
    {
        if(!strcmp(temp_buffer, variable_massive[i]))
        {
            root->data = (double)i;
            root->type_node = 3;
            MARKER = 1;
            break;
        }
    }

    if(MARKER == 0)
    {
        root->data = atoi(temp_buffer);
        root->type_node = 1;
    }
    
    
    char* start_buffer_son1 = buffer + end_root_data + 1;
    
    size_t dif_of_staples = 1;
    
    size_t open_staple;
    
    size_t close_staple;
    
    char* temp = start_buffer_son1 + 2;

    
    while(dif_of_staples != 0)
    {
        open_staple = (size_t)(strchr(temp, '(') - temp + 1);
        close_staple = (size_t)(strchr(temp, ')') - temp + 1);
        
        if(open_staple < close_staple)
        {
            temp = temp + open_staple;
            dif_of_staples = dif_of_staples + 1;
        }
        else
        {
            temp = temp + close_staple;
            dif_of_staples = dif_of_staples - 1;
        }
    }
    
    size_t son2_buffer_end = (size_t)(strrchr(temp + 1, ')') - (temp + 1));
    char* son2_buffer = (char*) calloc(size_buffer, sizeof(char));
    char* son1_buffer = (char*) calloc(size_buffer, sizeof(char));
    son1_buffer = strcpy(son1_buffer, start_buffer_son1);
    son1_buffer[temp - start_buffer_son1] = '\0';
    son2_buffer = strcpy(son2_buffer, temp);
    son2_buffer[son2_buffer_end + 1] = '\0';

    // printf("buffer = %s\n", buffer);
    // printf("son1_buffer = %s\n", son1_buffer);
    // printf("son2_buffer = %s\n", son2_buffer);
    

    root->son1 = ReadRoot(son1_buffer, size_buffer);
    root->son2 = ReadRoot(son2_buffer, size_buffer);

    free(son1_buffer);
    free(son2_buffer);
    free(temp_buffer);
    return root;
}

/********************************************************************************************************/

size_t TreeDestroy(struct tree* root)
{
    if (root == NULL)
    {
        return 0;
    }

    size_t quantity_destroy = 0;

    // fprintf(stderr, "here_destroy %p\n", root); 

    quantity_destroy = quantity_destroy + TreeDestroy(root->son1);

    quantity_destroy = quantity_destroy + TreeDestroy(root->son2);

    root->data = 0;
    root->type_node = 0;
    free(root);
    quantity_destroy = quantity_destroy + 1;
    
    return quantity_destroy;
}