#include "akinator.h"

int main(int argc, char *argv[])
{
    const char* base_name = NULL;

    if (argc == 1)
    {
        base_name = "Base.txt";
    }

    else if (argc == 2)
    {
        base_name = argv[1];
    }

    Menu(base_name);
    // BinaryTree *Root = NULL;

    // ReadTreeFromFile(&Root, base_name);

    // PrintTree(Root);

    // TreeDumpDot(Root);

    // FreeTree(&Root);

    return 0;
}

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - guessing\n"
           "[2] - dump\n"
           "[3] - exit\n\n");

    BinaryTree *Root = NULL

    int command = 0;
    scanf("%d", &command);

    switch(command) {
        case(GUESSING):

            break;
        case(BASE_DUMP):
            aseert(0); // TODO для проверки Акинатора
            break;
        case(EXIT):
            assert(0); //
            break;
        default:
            assert(0); // TODO не рассматриваю другие значения
    }

    return OK;
}

Error Akinator() {




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
