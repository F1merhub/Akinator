#include "akinator.h"

// Errors Akinator() {
//
//     BinaryTree *Root = NULL;
//     char buffer[ANSWER_BUFFER_SIZE] = {0};
//     ReadTreeFromFile(&Root, "Base.txt");
//
//     AkinatorPlay(Root);
//     PrintTree(&Root);
// //     while (1) {
// //
// //         printf("Хотите сыграть снова?\n"
// //            "Ваш ответ: ");
// //         assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
// //             buffer[strlen(buffer) - 1] = '\0';
// //
// //         if (strcmp(buffer, "n") == 0) {
// //             break;
// //         }
// //         else if (strcmp(buffer, "y") == 0) {
// //             printf("\npupu\n");
// //             AkinatorPlay(Root);
// //         }
// //         else
// //             assert(0); // добавить другие значения
// //     }
// //
// //     PrintTree(Root);
// //
// //     FreeTree(&Root);
//     return OK;
// }

Errors AkinatorPlay(BinaryTree *Root) {
    assert(Root != NULL);
    assert((Root->left != NULL) || (Root->right != NULL));

    BinaryTree *cur = Root;

    system("cls||clear");

    char buffer[ANSWER_BUFFER_SIZE] = {0};

    while (cur->left != NULL || cur->right != NULL) {
        assert(cur->left != NULL && cur->right != NULL);
        printf("Это ""%s?\n"
               "Ваш ответ: ", cur->value);

        assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL); // TODO поставить проверку
        buffer[strlen(buffer) - 1] = '\0';

        if (strcmp(buffer, "y") == 0) {
            cur = cur->right;
        }
        else if (strcmp(buffer, "n") == 0) {
            cur = cur->left;
        }
        else {
            assert(0); // TODO поправить на всевозможные ответы
        }

        assert(cur != NULL);
    }
    printf("Это ""%s?\n"
           "Ваш Ответ: ", cur->value);

    assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            buffer[strlen(buffer) - 1] = '\0';

    if (strcmp(buffer, "y") == 0) {
            printf("\nЯ угадал!");
    }
    else if (strcmp(buffer, "n") == 0) {
        printf("Кто это был?\n"
                "Ваш Ответ: ");

        CreateNode(&(cur->right), NULL);
        CreateNode(&(cur->left), NULL);
        cur->right->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
        cur->left->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));

        assert(fgets(cur->right->value, MAX_LINE_LENGTH, stdin) != NULL);
        (cur->right->value)[strlen(cur->right->value) - 1] = '\0';

        strcpy(cur->left->value, cur->value);

        printf("Чем %s отличается от %s?\n"
                "Ваш Ответ: ", cur->right->value, cur->value);

        assert(fgets(cur->value, MAX_LINE_LENGTH, stdin) != NULL);
        (cur->value)[strlen(cur->value) - 1] = '\0';
        PrintTree(Root);
        printf("\n");
    }
    else {
        assert(0); // TODO поправить на всевозможные ответы
    }

    return OK;
}

int main() {
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
    AkinatorPlay(Root);
    PrintTree(Root);
    FreeTree(&Root);
    return 0;
}
