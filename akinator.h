#ifndef akinator_H
#define akinator_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define TREE_ELEMENT_CHAR // NOTE в акинаторе используются лишь строки, для ввода типа данных нужно менять compare_value для вывода ошибок, а не assert

#if defined(TREE_ELEMENT_CHAR)

typedef char* tree_element;
#define TREE_ELEM_SPEC "%s"
#define TREE_ELEM_TYPE STRING
#elif defined(TREE_ELEMENT_INT)

typedef int tree_element;
#define TREE_ELEM_SPEC "%d"
#define TREE_ELEM_TYPE INT
#else

#error "Error"

#endif

typedef struct BinaryTree
{
    tree_element value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

enum Errors
{
    OK                    = 0,
    ALLOC_ERROR           = 1,
    NODE_NULL             = 2,
    FILE_NOT_OPEN         = 3,
    FILE_FORMAT_ERROR     = 4,
    FILE_ERROR            = 5,
};

enum Type
{
    STRING = 0,
    INT    = 1,
};

enum Mode
{
    GUESSING  = 1,
    BASE_DUMP = 2,
    EXIT      = 10,
};

enum Keys
{
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53
};

const size_t DUMP_BUFFER_SIZE = 20000;
const int ANSWER_BUFFER_SIZE = 30;

Errors CreateNode(BinaryTree **Node, tree_element value);
Errors FreeTree(BinaryTree **Node);
Errors AddNode(BinaryTree **Root, tree_element value);
BinaryTree* FindNode(BinaryTree *Root, tree_element value);
Errors AddNodeLoop(BinaryTree **Root, tree_element value);
Errors DeleteNode(BinaryTree **Root, tree_element value);
Errors TreeDumpDot(BinaryTree *Root);
int GenerateGraph(BinaryTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE);
int CompareValue(tree_element a, tree_element b);
Errors ReadTreeFromFile(BinaryTree** root, const char* base_name);
Errors ParseSubtree(FILE* base, BinaryTree** node);
Errors TreeTraversal(BinaryTree *Node, int level);
Errors PrintTree(BinaryTree *Root);
char* trim_whitespace(char* str);
Errors ReadTreeFromFile(BinaryTree** Root, const char* filename);
Errors ParseSubtree(FILE* file, BinaryTree** Node);
char* trim_whitespace(char* str);
Errors AkinatorMenu(BinaryTree *Root);
void AkinatorPlay(BinaryTree *Root);
Errors Menu(const char* base_name);
Errors AkinatorMode(const char* base_name);
Errors Akinator(BinaryTree *Root);

#endif // akinator_H
