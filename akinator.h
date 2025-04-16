#ifndef akinator_H
#define akinator_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
// #include "stack.h"

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

#define COLOR_RED "\x1b[31m"

#define NULL_CHECK_AND_RETURN(pointer)      \
    do {                                    \
        if (pointer == NULL) {              \
            return MEMORY_ALLOCATION_ERROR; \
        }                                   \
    } while(0)                              \

#define CALL_AND_RETURN_ERROR(func_call)    \
    do {                                    \
        Errors error = (func_call);         \
        if (error != OK) {                  \
            return error;                   \
        }                                   \
    } while(0)                              \


struct Stack;

typedef struct BinaryTree
{
    tree_element value;
    struct BinaryTree *left;
    struct BinaryTree *right;
} BinaryTree;

enum Errors
{
    OK                       = 0,
    MEMORY_ALLOCATION_ERROR  = 1,
    FILE_NOT_OPEN            = 3,
    FILE_FORMAT_ERROR        = 4,
    STDIN_ERROR              = 6,
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
    KEY_5 = 53,
    KEY_COUNT
};

const size_t DUMP_BUFFER_SIZE = 20000;
const int ANSWER_BUFFER_SIZE = 30;

Errors CreateNode(BinaryTree **Node, tree_element value);
Errors FreeTree(BinaryTree **Node);
Errors AddNode(BinaryTree **Root, tree_element value);
BinaryTree* FindNodeSortTree(BinaryTree *Root, tree_element value);
Errors AddNodeLoop(BinaryTree **Root, tree_element value);
Errors DeleteNode(BinaryTree **Root, tree_element value);
Errors TreeDumpDot(BinaryTree *Root);
int GenerateGraph(BinaryTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE);
int CompareValue(tree_element a, tree_element b);
Errors ReadTreeFromFile(BinaryTree** root, const char* base_name);
Errors ParseTree(FILE* base, BinaryTree** node);
Errors TreeTraversal(BinaryTree *Node, int level);
Errors PrintTree(BinaryTree *Root);
char* CutString(char* str);
Errors AkinatorMenu(BinaryTree *Root, const char* base_name);
Errors AkinatorPlay(BinaryTree *Root);
Errors Menu(const char* base_name);
Errors AkinatorMode(const char* base_name);
Errors Akinator(BinaryTree *Root, const char* base_name);
BinaryTree* CheckObjectExistance(BinaryTree *Root, tree_element value);
int GetAnswer();
char* GetObject();
Errors DefinitionMode(const char* name_base);
Errors Definition(BinaryTree *Root, const char* base_name);
Stack* FindNodePath(const char* value, BinaryTree *Root);
int FindNode(const char* value, BinaryTree *Node, Stack* node_path);
Errors DefinitionMenu(BinaryTree *Root, const char *base_name);
Errors ComparingMode(const char *base_name);
Errors Comparing(BinaryTree *Root, const char *base_name);
void clean_console();
Errors ComparingMenu(BinaryTree *Root, const char *base_name);
int GetMode(int mode_count);
void PrintError(Errors error);
const char* ErrorsDecoder(Errors error);
Errors BaseDump(const char *base_name);


#endif // akinator_H
