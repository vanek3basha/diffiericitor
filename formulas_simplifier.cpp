#include "header/operator_function.h"
#include "header/formulas_simplifier.h"

struct tree* SimplifierTree(struct tree* root)
{
    if (root == NULL) {
        fprintf(stderr, "SimplifierTree: got NULL\n");
        return NULL;
    }

    // fprintf(stderr, "simplehere %p\n", root);
    struct tree* new_root = COPY_(root);
    // fprintf(stderr, "simplehere %p\n", new_root);
    struct tree* end_root;
    
    if(new_root->son1 != NULL)
    {
        TreeDestroy(new_root->son1);
        new_root->son1 = SimplifierTree(root->son1);
    }
    
    if(new_root->son2 != NULL)
    {
        TreeDestroy(new_root->son2);
        new_root->son2 = SimplifierTree(root->son2);
    }


    if(new_root->son2 != NULL && new_root->son1 != NULL)
    {
        if(new_root->son1->type_node == NUMBER && iszero(new_root->son1->data - 1) && new_root->type_node == OPERATOR && (int)new_root->data == MUL)
        {
            end_root = COPY_(new_root->son2);
            TreeDestroy(new_root);
            return end_root;
        }
        else if(new_root->son2->type_node == NUMBER && iszero(new_root->son2->data - 1) && new_root->type_node == OPERATOR && ((int)new_root->data == MUL || (int)new_root->data == DIF))
        {
            end_root = COPY_(new_root->son1);
            TreeDestroy(new_root);
            return end_root;
            
        }
        else if(new_root->son2->type_node == NUMBER && iszero(new_root->son2->data) && new_root->type_node == OPERATOR && ((int)new_root->data == ADD || (int)new_root->data == SUB))
        {
            end_root = COPY_(new_root->son1);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(new_root->son1->type_node == NUMBER && iszero(new_root->son1->data) && new_root->type_node == OPERATOR && ((int)new_root->data == ADD /*|| (int)root->data == SUB*/))
        {
            end_root = COPY_(new_root->son2);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(((iszero(new_root->son1->data) && new_root->son1->type_node == NUMBER) || (iszero(new_root->son2->data) && new_root->son2->type_node == NUMBER)) \
                                                                            && new_root->type_node == OPERATOR && (int)new_root->data == MUL)
        {
            end_root = NUM_(0);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(iszero(new_root->son1->data) && new_root->son1->type_node == NUMBER && new_root->type_node == OPERATOR && (int)new_root->data == DIF)
        {
            end_root = NUM_(0);
            TreeDestroy(new_root);
            return end_root;

        }
        
        else if(new_root->son1->type_node == NUMBER && new_root->son2->type_node == NUMBER && new_root->type_node == OPERATOR && (int)new_root->data == ADD)
        {
            end_root = NUM_(new_root->son1->data + new_root->son2->data);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(new_root->son1->type_node == NUMBER && new_root->son2->type_node == NUMBER && new_root->type_node == OPERATOR && (int)new_root->data == MUL)
        {
            end_root = NUM_(new_root->son1->data * new_root->son2->data);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(new_root->son1->type_node == NUMBER && new_root->son2->type_node == NUMBER && new_root->type_node == OPERATOR && (int)new_root->data == SUB)
        {
            end_root = NUM_(new_root->son1->data - new_root->son2->data);
            TreeDestroy(new_root);
            return end_root;

        }
        else if(new_root->son1->type_node == NUMBER && new_root->son2->type_node == NUMBER && new_root->type_node == OPERATOR && (int)new_root->data == DIF)
        {
            end_root = NUM_(new_root->son1->data / new_root->son2->data);
            TreeDestroy(new_root);
            return end_root;

        }

        else
        {
            end_root = COPY_(new_root);
            TreeDestroy(new_root);
            return end_root;
        }
    }
    else
    {
        return new_root;
    }
}


/**************************************************************************************************/

int iszero(double a)
{
    if(fabs(a) > EPS)
    {
        return 0;
    } 
    else
    {
        return 1;
    }
}