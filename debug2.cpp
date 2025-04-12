#include "akinator.h"
#include "stack.h"

int main() {
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");

    Stack *node_path = FindNodePath("poltarashka", Root);
    stack_dump(node_path);
    TreeDumpDot(Root);
    stack_destructor(node_path);
    FreeTree(&Root);
    return 0;
}
