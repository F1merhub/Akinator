#include "akinator.h"

void AddNewTreeObject(BinaryTree *cur, char *buffer, char *feature_buffer) { // указатель на узел, Кто это был, затем признак
    assert(cur != NULL && buffer != NULL && feature_buffer != NULL);
    CreateNode(&(cur->left), cur->value);
    CreateNode(&(cur->right), buffer);
    cur->value = feature_buffer;
}

int main() {
    char buffer[ANSWER_BUFFER_SIZE] = {0};
    char feature_buffer[ANSWER_BUFFER_SIZE] = {0};
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
    BinaryTree *cur = Root;
    cur = cur->right->left;
    strcpy(buffer, "pushistick");
    strcpy(feature_buffer, "beliy");
    AddNewTreeObject(cur, buffer, feature_buffer);
    PrintTree(Root);


    return 0;
}
