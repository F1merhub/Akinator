#include "akinator.h"

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - Угадывание\n"


           "[4] - Распечатка Базы данных\n"
           "[5] - Выход\n"
           "Ваш ответ: ");

    int command = 0;
    command = getchar();
    getchar(); // пропустить \n

    switch(command) {
        case(KEY_1): // Акинатор
            AkinatorMode(base_name);
            break;
        case(KEY_4):// TODO распечатка
            break;
        case(KEY_5):
            printf("exit from menu");
            break;
        default:
            assert(0); // NOTE пока только два режима
    }

    return OK;
}

Errors AkinatorMode(const char* base_name) {

    assert(base_name != NULL);

    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, base_name); // TODO проверка на нормальное дерево
    Akinator(Root, base_name);

    return OK;
}

Errors Akinator(BinaryTree *Root, const char* base_name) {

    assert(base_name != NULL);
    assert(Root != NULL);

    printf("Добро Пожаловать в Акинатор\n"
           "Я буду спрашивать признак, а ты отвечай y/n\n");
    AkinatorPlay(Root);
    AkinatorMenu(Root, base_name);
    return OK;
}

Errors AkinatorMenu(BinaryTree *Root, const char* base_name) {

    printf("Выберите Режим\n"
            "[1] - Играть\n"
            "[2] - Сохранить Базу данных\n" // TODO сохранить в файл базу
            "[3] - Выход\n"
            "Ваш ответ: ");

    int command = 0;
    command = getchar();
    getchar(); // пропустить \n

    switch(command) {
        case(KEY_1):
            Akinator(Root, base_name);
            break;
        case(KEY_3):
            FreeTree(&Root);
            Menu(base_name);
            break;
        default:
            assert(0);
    }

    return OK;
}

void AkinatorPlay(BinaryTree *Root) {

    assert(Root != NULL);

    BinaryTree *cur = Root;
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

        char *object_buffer = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
        assert(fgets(object_buffer, MAX_LINE_LENGTH, stdin) != NULL);
        object_buffer[strlen(object_buffer) - 1] = '\0';
        if (FindNodeAkinator(Root, object_buffer) != NULL) {
            printf("Объект был найден в базе данных\n"
                   "Попробуйте сыграть еще раз\n");
        }
        else {
            CreateNode(&(cur->right), NULL);
            CreateNode(&(cur->left), NULL);
            cur->right->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
            cur->left->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));

            strcpy(cur->right->value, object_buffer);
            strcpy(cur->left->value, cur->value);

            printf("Чем %s отличается от %s?\n"
                   "Ваш Ответ: ", cur->right->value, cur->value);

            assert(fgets(cur->value, MAX_LINE_LENGTH, stdin) != NULL);
            (cur->value)[strlen(cur->value) - 1] = '\0';
        }
    }
    else {
        assert(0); // TODO поправить на всевозможные ответы
    }

}

int main() {

    Menu("Base2.txt");

    return 0;
}
