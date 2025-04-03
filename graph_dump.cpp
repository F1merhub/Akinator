#include <stdio.h>
#include <stdlib.h>
#include "akinator.h"

TreeErrors TreeDumpDot(BinaryTree* Root)
{
    char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return ALLOC_ERROR;
    }

    int buffer_len = 0;

    // Начало .dot файла
    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len,
                           "digraph G {\n"
                           "\trankdir = TB;\n"
                           "\tbgcolor=\"#1e1e2e\";\n"
                           "\tnode [shape=rectangle, style=filled, fontname=Helvetica, fontsize=12, fillcolor=\"#89b4fa\", color=\"#cba6f7\", fontcolor=\"#1e1e2e\"];\n");

    // Генерация графа
    buffer_len += GenerateGraph(Root, buffer, &buffer_len, BUFFER_SIZE);

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len, "}\n");

    FILE* dump_file = fopen("GraphDump/dump.dot", "w+");
    if (!dump_file)
    {
        fprintf(stderr, "Failed to open dump.dot\n");
        free(buffer);
        return FILE_NOT_OPEN;
    }

    fprintf(dump_file, "%s", buffer);

    fclose(dump_file);
    free(buffer);

    return OK;
}

int GenerateGraph(BinaryTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE)
{
    if (!Node) return 0;

    *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                            "\tnode%p [shape=plaintext; style=filled; color=\"#fcf0d2\"; fillcolor=\"#b2d4fc\"; label = <\n"
                            "\t\t         <table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"6\" BGCOLOR=\"#a1c4fd\" COLOR=\"#4f4f4f\">\n"
                            "\t\t\t           <tr><td align='center' colspan='2'><FONT COLOR='#3b4252'><b>Node: %p</b></FONT></td></tr>\n"
                            "\t\t\t           <tr><td align='center' colspan='2'><FONT COLOR='#2e8b57'>Value: <b>" TREE_ELEM_SPEC "</b></FONT></td></tr>\n"
                            "\t\t\t           <tr>\n"
                            "\t\t\t               <td WIDTH='150' PORT='left'  align='center'><FONT COLOR='#006400'><b>Left: %p</b></FONT></td>\n"
                            "\t\t\t               <td WIDTH='150' PORT='right' align='center'><FONT COLOR='#b94e48'><b>Right: %p</b></FONT></td>\n"
                            "\t\t\t           </tr>\n"
                            "\t\t         </table> >];\n",
                            Node, Node, Node->value, Node->left, Node->right);

    // Рекурсивно генерируем левое поддерево
    if (Node->left)
    {
        *buffer_len += GenerateGraph(Node->left, buffer, buffer_len, BUFFER_SIZE);
        *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                                 "\tnode%p:left -> node%p [color=\"#a6e3a1\"]\n", Node, Node->left);
    }

    // Рекурсивно генерируем правое поддерево
    if (Node->right)
    {
        *buffer_len += GenerateGraph(Node->right, buffer, buffer_len, BUFFER_SIZE);
        *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                                 "\tnode%p:right -> node%p [color=\"#f9e2af\"]\n", Node, Node->right);
    }

    return 0;
}
