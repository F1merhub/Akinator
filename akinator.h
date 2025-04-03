#ifndef akinator_H
#define akinator_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TREE_ELEMENT_CHAR // NOTE в акинаторе используются лишь строки, для ввода типа данных нужно менять compare_value для вывода ошибок, а не assert

#if defined(TREE_ELEMENT_CHAR)

typedef const char* tree_element;
#define TREE_ELEM_SPEC "%s"

#elif defined(TREE_ELEMENT_INT)

typedef int tree_element;
#define TREE_ELEM_SPEC "%d"

#else

#error "Error"

#endif

typedef struct BinaryTree
{
    tree_element value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

enum Type
{
    INT =    1,
    STRING = 2,
    DOUBLE = 3,
};


enum TreeErrors
{
    OK                    = 0,
    ALLOC_ERROR           = 1,
    NODE_NULL             = 2,
    FILE_NOT_OPEN         = 3,
    UNKNOWN_TYPE          = 4
};

const enum Type TREE_ELEMENT_TYPE = STRING; // как сделать по другому?
const size_t BUFFER_SIZE = 20000;


TreeErrors CreateNode(BinaryTree **Node, tree_element value);
TreeErrors FreeTree(BinaryTree **Node);
TreeErrors AddNode(BinaryTree **Root, tree_element value);
BinaryTree* FindNode(BinaryTree *Root, tree_element value);
TreeErrors TreeTraversal(BinaryTree *Node);
TreeErrors AddNodeLoop(BinaryTree **Root, tree_element value);
TreeErrors DeleteNode(BinaryTree **Root, tree_element value);
TreeErrors TreeDumpDot(BinaryTree *Root);
int GenerateGraph(BinaryTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE);
int CompareValue(tree_element a, tree_element b);

#endif // akinator_H
