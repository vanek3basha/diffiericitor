#include "header/reader.h"
#include "header/gener_tree_dump.h"
#include <string.h>
#include <ctype.h>


struct tree* ParsingNumber(char** expression)
{
    skip_spaces(expression);
    
    double value = 0;
    
    while(isdigit(**expression))
    {
        value = value * 10 + (**expression - '0');
        (*expression)++;
        // fprintf(stderr, "%c here_pars_num\n", **expression);
    }
    

    if(**expression == '.')
    {
        (*expression)++;
        double decimal_place = 10;
        while(isdigit(**expression))
        {
            value += (**expression - '0') / decimal_place;
            decimal_place *= 10;
            (*expression)++;
        }
    }

    return CreateNumberNode(value);
}

/**********************************************************************************************************************/

struct tree* ParsingOperator(char** expression, struct data_baze_of_variable* VAR)
{
    skip_spaces(expression);
    int i = isoperator(*expression) - 1;
    int num_operator = date_baza_operators[i].num;
    struct tree* node;

    (*expression) = (*expression) + date_baza_operators[i].count_of_simbol;
    
    if(num_operator >= 7 )
    {
        node = CreateOperatorNode(num_operator);
        if(node == NULL)
        {
            perror("Create operator ERROR\n");
            return NULL;
        }
        
        skip_spaces(expression);

        if(**expression == '(')
        {
            node->son1 = ParsingSkobka(expression, VAR);
        }

        else
        {
            perror("OPERATOR DON'T HAVE ()\n");
            return NULL;
        }

        return node;
    }
    else if(num_operator == 6)
    {
        node = CreateOperatorNode(num_operator);
        if(node == NULL)
        {
            perror("Create operator ERROR\n");
            return NULL;
        }
        
        skip_spaces(expression);

        if(**expression == '(')
        {
            node->son1 = ParsingSkobka(expression, VAR);
        }

        else
        {
            perror("OPERATOR DON'T HAVE ()\n");
            return NULL;
        }

        skip_spaces(expression);

        if(**expression == '(')
        {
            node->son2 = ParsingSkobka(expression, VAR);
        }
        else
        {
            perror("OPERATOR DONT HAVE SECOND ()\n");
            return NULL;
        }

        return node;
    }
    else
    {
        node = CreateOperatorNode(num_operator);
        if(node == NULL)
        {
            perror("Create operator ERROR\n");
            return NULL;
        }
        return node;
    }
    
}

/**********************************************************************************************************************/

struct tree* ParsingSkobka(char** expression, struct data_baze_of_variable* VAR)
{
    massive_for_token* tok = token_init(100);
    (*expression) = (*expression) + 1;
    
    skip_spaces(expression);
    while(**expression != ')')
    {
        // fprintf(stderr, "here_skopka\n");
        skip_spaces(expression);
        
        if (isdigit(**expression))
        {
            token_push(&tok, ParsingNumber(expression), 0);
        }
        else if(isoperator(*expression))
        {
            token_push(&tok, ParsingOperator(expression, VAR), 0);
        }
        else if((**expression) == '(')
        {
            token_push(&tok, ParsingSkobka(expression, VAR), 1);
        }
        else if(isalpha(**expression))
        {
            token_push(&tok, ParsingVariable(expression, VAR), 0);
        }
        else
        {
            break;
        }
        
        skip_spaces(expression);
    }
    *expression = *expression + 1;
    
    // for(size_t i = 0; i < tok->size; i++)
    // {
    //     printf("%f size - %zu\n", tok->data[i]->data, tok->size);
    // }


    struct tree* node = SborkaLineynogoVirazzheniya(tok);
    token_destroy(tok);
    // FILE* dot_file = fopen("dot_file_skobka.dot", "w");
    
    // if (dot_file == NULL)
    // {
    //     perror("ERROR FOR OPEN DOT FILE");
    //     return NULL;
    // }

    // save_tree_to_dot_string(node, dot_file);

    // fclose(dot_file);

    // system("dot -Tpng dot_file_skobka.dot -o graph_scobka.png");
    return node;
}

/**********************************************************************************************************************/

struct tree* ParsingVariable(char** expression, struct data_baze_of_variable* VAR)
{
    skip_spaces(expression);
    char* time_expression = *expression;
    char var_name[100];
    size_t name_lenght = 0;
    size_t var_num;
    size_t MARKER_EXISTENCE = 0;
    //чтение имени
    while(isalnum(*time_expression))
    {
        time_expression = time_expression + 1;
        name_lenght = name_lenght + 1;
    }

    for(size_t i = 0; i < name_lenght; i++)
    {
        var_name[i] = **expression;
        (*expression) = (*expression) + 1;
    }
    
    // fprintf(stderr, "expression \'%c\'\n", **expression);
    // fprintf(stderr, "%ld\n", time_expression - (*expression));

    var_name[name_lenght] = '\0';
    // fprintf(stderr, "%s\n", var_name);
    //проверка на наличие в массиве переменных
    for(size_t i = 0; i < VAR->count_of_variable; i++)
    {
        if(!strcmp(VAR->MASSIVE_OF_VARIABLE[i], var_name))
        {
            MARKER_EXISTENCE = 1;
            var_num = i;
        }
    }

    if(MARKER_EXISTENCE == 0)
    {
        VAR->MASSIVE_OF_VARIABLE[VAR->count_of_variable] = (char*)calloc(strlen(var_name) + 1, sizeof(char));
        if(VAR->MASSIVE_OF_VARIABLE[VAR->count_of_variable] == NULL)
        {
            perror("calloc stroka ERROR");
            return NULL;
        }
        strcpy(VAR->MASSIVE_OF_VARIABLE[VAR->count_of_variable], var_name);
        var_num = VAR->count_of_variable;
        VAR->count_of_variable = VAR->count_of_variable + 1;
        if(VAR->count_of_variable + 1 >= VAR->capacity)
        {
            VAR = var_struct_realloc(VAR, VAR->capacity * 2);
        }
    }

    // fprintf(stderr, "reader %s\n", VAR->MASSIVE_OF_VARIABLE[0]);



    skip_spaces(expression);
    return CreateVariableNode((double)var_num);
}

/**********************************************************************************************************************/

struct tree* Parsing(char** expression, struct data_baze_of_variable* VAR)
{
    massive_for_token* tok = token_init(20);
    // fprintf(stderr, "while_count %d\n", isoperator(*expression));
    skip_spaces(expression);
    
    while(1)
    {
        skip_spaces(expression);
        // fprintf(stderr, "expression \'%c\'\n", **expression);
        
        if (isdigit(**expression))
        {
            token_push(&tok, ParsingNumber(expression), 0);
        }
        else if(isoperator(*expression))
        {
            token_push(&tok, ParsingOperator(expression, VAR), 0);
        }
        else if((**expression) == '(')
        {
            token_push(&tok, ParsingSkobka(expression, VAR), 1);
        }
        else if(isalpha(**expression))
        {
            token_push(&tok, ParsingVariable(expression, VAR), 0);
        }
        else
        {
            break;
        }
        skip_spaces(expression);
    }


    // for(size_t i = 0; i < tok->size; i++)
    // {
    //     printf("%f size - %zu\n", tok->data[i]->data, tok->size);
    // }

    struct tree* node = SborkaLineynogoVirazzheniya(tok);
    token_destroy(tok);
    return node;
    
}

/**********************************************************************************************************************/

struct tree* SborkaLineynogoVirazzheniya(massive_for_token* tok)
{
    size_t Marker_No_Plus = 0;
    size_t Marker_No_Mul = 0;
    size_t Marker_No_Pow = 0;
    
    for(size_t i = 0; i < tok->size; i++)
    {
        if(tok->data[i]->data <= 2 && tok->data[i]->type_node == 2 && tok->scobka[i] == 0)
        {
            // fprintf(stderr, "here\n");
            massive_for_token* tok1 = token_init(100);
            massive_for_token* tok2 = token_init(100);
            for(size_t g = 0; g < i; g++)
            {
                token_push(&tok1, tok->data[g], tok->scobka[g]);
            }
            for(size_t g = i; g < tok->size - 1; g++)
            {
                token_push(&tok2, tok->data[g + 1], tok->scobka[g + 1]);
            }
            // fprintf(stderr, "%zu zero\n", tok2->size);
            struct tree* node = tok->data[i];
            node->son1 = SborkaLineynogoVirazzheniya(tok1);
            // fprintf(stderr, "%f zero\n", node->son1->data);
            node->son2 = SborkaLineynogoVirazzheniya(tok2);
            token_destroy(tok1);
            token_destroy(tok2);
            
            return node;
        }
        else
        {
            Marker_No_Plus = 1;
        }
    }
    // fprintf(stderr, "after return\n");
    if(Marker_No_Plus == 1)
    {
        for(size_t i = 0; i < tok->size; i++)
        {
            if(tok->data[i]->data <= 4 && tok->data[i]->type_node == 2 && tok->scobka[i] == 0)
            {
                massive_for_token* tok1 = token_init(100);
                massive_for_token* tok2 = token_init(100);
                for(size_t g = 0; g < i; g++)
                {
                    token_push(&tok1, tok->data[g], tok->scobka[g]);
                }
                for(size_t g = i; g < tok->size - 1; g++)
                {
                    token_push(&tok2, tok->data[g + 1], tok->scobka[g + 1]);
                }
                
                struct tree* node = tok->data[i];
                node->son1 = SborkaLineynogoVirazzheniya(tok1);
                node->son2 = SborkaLineynogoVirazzheniya(tok2);
                token_destroy(tok1);
                token_destroy(tok2);
                return node;
            }
            else
            {
                Marker_No_Mul = 1;
            }
        }
    }
    if(Marker_No_Mul == 1 && Marker_No_Plus == 1)
    {
        for(size_t i = 0; i < tok->size; i++)
        {
            if(tok->data[i]->data <= 5 && tok->data[i]->type_node == 2 && tok->scobka[i] == 0)
            {
                massive_for_token* tok1 = token_init(100);
                massive_for_token* tok2 = token_init(100);
                for(size_t g = 0; g < i; g++)
                {
                    token_push(&tok1, tok->data[g], tok->scobka[g]);
                }
                for(size_t g = i; g < tok->size - 1; g++)
                {
                    token_push(&tok2, tok->data[g+1], tok->scobka[g + 1]);
                }
                struct tree* node = tok->data[i];
                node->son1 = SborkaLineynogoVirazzheniya(tok1);
                node->son2 = SborkaLineynogoVirazzheniya(tok2);
                token_destroy(tok1);
                token_destroy(tok2);
                return node;
            }
            else
            {
                Marker_No_Pow = 1;
            }
        }
    }
    if(Marker_No_Mul == 1 && Marker_No_Plus == 1 && Marker_No_Pow == 1)
    {
        return tok->data[0];
    }


    return NULL;
}

/**********************************************************************************************************************/

void skip_spaces(char** expression)
{
    while(**expression == ' ' || **expression == '\t')
    {
        *expression = *expression + 1;
    }
}

/**********************************************************************************************************************/

int isoperator(char* expression)
{
    skip_spaces(&expression);
    // fprintf(stderr, "here1 %s\n", expression);
    for(int i = 0; date_baza_operators[i].name !=0; i++)
    {
        if(!strncmp(date_baza_operators[i].name, expression, date_baza_operators[i].count_of_simbol))
        {
            // fprintf(stderr, "here2\n");
            if(i <= 5)
            {
                return i + 1;
            }
            else
            {
                if(isspace(expression[date_baza_operators[i].count_of_simbol]) || expression[date_baza_operators[i].count_of_simbol] == '(' )
                { 
                    return i + 1;
                }
            }
        }
    }
    return 0;
}
