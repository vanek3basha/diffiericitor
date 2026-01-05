#include "header/gener_tree_dump.h"
#include "header/new_tree.h"
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////

void generate_dot_string(struct tree* root, FILE *file) 
{
    if (root == NULL)
    {
        return;
    } 
    
    // fprintf(stderr, "here dot\n");
        
    static int null_count = 0;
    static int node_count = 0;
    int current_id = node_count++;

    if(root->type_node == NUMBER)
    {
    fprintf(file, "  node_%d [label=\"adres = %p | {data = %f | type = NUMBER} | {son1 = %p | son2 = %p} \", shape=record, style=\"filled,rounded\", fillcolor=lightblue, width=0.8, height=0.6];\n",  \
            current_id, root, root->data, root->son1, root->son2);
    }
    if(root->type_node == OPERATOR)
    {
    fprintf(file, "  node_%d [label=\"adres = %p | {data = %f | type = OPERATOR} | {son1 = %p | son2 = %p} \", shape=record, style=\"filled,rounded\", fillcolor=lightblue, width=0.8, height=0.6];\n",  \
            current_id, root, root->data, root->son1, root->son2);
    }
    if(root->type_node == VARIABLE)
    {
    fprintf(file, "  node_%d [label=\"adres = %p | {data = %f | type = VARIABLE} | {son1 = %p | son2 = %p} \", shape=record, style=\"filled,rounded\", fillcolor=lightblue, width=0.8, height=0.6];\n",  \
            current_id, root, root->data, root->son1, root->son2);
    }


    if (root->son1 != NULL) 
    {
        int left_id = node_count;
        fprintf(file, "  node_%d -> node_%d [color=blue, penwidth=2];\n", current_id, left_id);
        generate_dot_string(root->son1, file);
    } 
    else 
    {
        fprintf(file, "  null_left_%d [label = NULL, shape=box, style=\"filled,rounded\", fillcolor=pink, width=0.8, height=0.6];\n", null_count);
        fprintf(file, "  node_%d -> null_left_%d [color=blue, style=dotted];\n", current_id, null_count);
        null_count++;
    }
    
    if (root->son2 != NULL) 
    {
        int right_id = node_count;
        fprintf(file, "  node_%d -> node_%d [color=red, penwidth=2];\n", current_id, right_id);
        generate_dot_string(root->son2, file);
    } 
    else 
    {
        fprintf(file, "  null_right_%d [label = NULL, shape=box, style=\"filled,rounded\", fillcolor=pink, width=0.8, height=0.6];\n", null_count);
        fprintf(file, "  node_%d -> null_right_%d [color=red, style=dotted];\n", current_id, null_count);
        null_count++;
    }
}

/******************************************************************************************************/

void save_tree_to_dot_string(struct tree* root, FILE* file) {
    
    fprintf(file, "digraph BST {\n");
    fprintf(file, "label=<<B>TREE</B>>;\n fontcolor=\"#008000\";\n fontname=\"Arial\";\n labelloc=\"top\";\n labeljust=\"left\";\n fontsize=20;\n\n\n");
    
    fprintf(file, "node[shape=box, width=0.7, height=0.4, style=\"filled, rounded\", fontname=\"Arial\"];\n\n\n\n");   
    
    
    
    
    if (root != NULL) {
        generate_dot_string(root, file);
    }
    
    fprintf(file, "}\n");
    
}