#include "akinator.h"

int main() {
    char buffer[ANSWER_BUFFER_SIZE] = {0};
    char feature_buffer[ANSWER_BUFFER_SIZE] = {0};
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
    BinaryTree *cur = Root;
    cur = cur->right->left;
    // // printf("%d", (cur->value)[11]);
    // // printf("%d", strlen(cur->value));
    // strcpy(buffer, "pushistick");
    // strcpy(feature_buffer, "beliy");
    // printf("%d %d \n", buffer[10], feature_buffer[5]);
    assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
        buffer[strlen(buffer) - 1] = '\0';

    assert(fgets(feature_buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
        feature_buffer[strlen(feature_buffer) - 1] = '\0';
    printf("%s %s %s\n", buffer, feature_buffer, cur->value);
    printf("%d %d %d", strlen(buffer), strlen(feature_buffer), strlen(cur->value));


    AddNewTreeObject(cur, buffer, feature_buffer);
    PrintTree(Root);

    FreeTree(&Root);
    return 0;
}
