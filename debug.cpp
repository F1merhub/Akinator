#include "akinator.h"

Errors AkinatorMenu(BinaryTree *Root) {

        printf("Выберите Режим\n" // добавить сохранение дерева
               "[1] - Играть\n"
               "[3] - Выход\n"
               "Ваш ответ: ");

        int command = 0;
        command = getchar();
        getchar(); // пропустить \n

        switch(command) {
            case(KEY_1):
                Akinator(Root);
                break;
            case(KEY_3):
                break;
            default:
                assert(0);
        }

    FreeTree(&Root);
    return OK;
}

void AkinatorPlay(BinaryTree *Root) { //TODO Проверка на плохую базу + добавить говорилку + проверка, что новый элемент уже существует
    assert(Root != NULL);

    BinaryTree *cur = Root;

    // system("cls||clear");

    char buffer[ANSWER_BUFFER_SIZE] = {0};

    while (cur->left != NULL || cur->right != NULL) {
        assert(cur->left != NULL && cur->right != NULL);
        printf("Это ""%s?\n"
               "Ваш ответ: ", cur->value);

        assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL); // TODO поставить проверку
        buffer[strlen(buffer) - 1] = '\0';
        // printf("\n%d\n", buffer[0]);
        if (strcmp(buffer, "y") == 0) {
            cur = cur->right;
        }
        else if (strcmp(buffer, "n") == 0) {
            cur = cur->left;
        }
        else {
            assert(0); // TODO поправить на всевозможные ответы, либо циклов for
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

    }
    else {
        assert(0); // TODO поправить на всевозможные ответы
    }

}

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - guessing\n"
           "[5] - exit\n\n");

    int command = 0;
    command = getchar();
    getchar(); // пропустить \n

    switch(command) {
        case(KEY_1): // Акинатор
            AkinatorMode(base_name);
            break;
        case(KEY_5):
            printf("exit in menu");
            break;
        default:
            assert(0); // NOTE пока только два режима
    }

    return OK;
}

Errors AkinatorMode(const char* base_name) {

    assert(base_name != NULL);

    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, base_name);
    Akinator(Root);

    return OK;
}

Errors Akinator(BinaryTree *Root) {
    assert(Root != NULL);
    printf("Добро Пожаловать в Акинатор\n"
           "Я буду спрашивать признак, а ты отвечай y/n\n");
    AkinatorPlay(Root);
    AkinatorMenu(Root);
    return OK;
}

int main() {

    Menu("Base.txt");

    return 0;
}
