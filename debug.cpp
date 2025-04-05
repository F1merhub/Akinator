#include "akinator.h"

Error Akinator() {

    BinaryTree *Root = NULL;
    char buffer[ANSWER_BUFFER_SIZE] = {0};

    AkinatorPlay(Root);

    while (1) {

        printf("Хотите сыграть снова?\n"
           "Ваш ответ: ");
        assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            buffer[strlen(buffer) - 1] = '\0';

        if (strcmp(buffer, "n")) {
            break;
        }
        else if (strcmp(buffer, "y")) {
            AkinatorPlay(Root);
        }
        else
            assert(0); // добавить другие значения
    }

    PrintTree(Root);
    
    TreeFree(&Root);
    return 0;
}

Error AkinatorPlay(BinaryTree *Root) {
    if (Root == NULL) { // Первая Игра
        ReadTreeFromFile(&Root, "Base.txt");
        BinaryTree *cur = Root;
    }

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

            assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            buffer[strlen(buffer) - 1] = '\0';

            printf("Чем %s отличается от %s?\n"
                   "Ваш Ответ: ", buffer, cur->value);

            char feature_buffer[ANSWER_BUFFER_SIZE] = {0};
            assert(fgets(feature_buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            feature_buffer[strlen(feature_buffer) - 1] = '\0';

            AddNewTreeObject(cur, buffer, feature_buffer);
        }
        else {
            assert(0); // TODO поправить на всевозможные ответы
        }

    return 0;
}

int main() {

    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
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

            assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            buffer[strlen(buffer) - 1] = '\0';

            printf("Чем %s отличается от %s?\n"
                   "Ваш Ответ: ", buffer, cur->value);

            char feature_buffer[ANSWER_BUFFER_SIZE] = {0};
            assert(fgets(feature_buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
            feature_buffer[strlen(feature_buffer) - 1] = '\0';

            AddNewTreeObject(cur, buffer, feature_buffer);
        }
        else {
            assert(0); // TODO поправить на всевозможные ответы
        }

    PrintTree(Root);
    FreeTree(&Root);
    return 0;
}
