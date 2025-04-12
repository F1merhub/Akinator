#include "akinator.h"

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - Угадывание\n"
           "[2] - Определение\n"
           "[3] - Сравнение\n"
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

Errors DefinitionMode(const char* base_name) {
    assert(base_name != NULL);
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, base_name);
    Definition(&Root, base_name);
}

Errors Definition(BinaryTree *Root, const char* base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите слово, определения которого хотите посомтреть\n"
           "Ваше слово: ");
    char *object = GetObject(); // TODO не забыть очистить память в конце




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

    while (cur->left != NULL || cur->right != NULL) {
        assert(cur->left != NULL && cur->right != NULL);

        printf("Это ""%s?\n"
               "Ваш ответ: ", cur->value);

        int answer = GetAnswer();
        switch (answer) {
            case(1):
                cur = cur->right;
                break;
            case(0):
                cur = cur->left;
                break;
            default:
                break;
        }

        assert(cur != NULL);
    }
    printf("Это ""%s?\n"
           "Ваш Ответ: ", cur->value);

    int answer = GetAnswer();
    switch (answer) {
        case(1):
            printf("\nЯ угадал!");
            break;
        case(0): {
            printf("Кто это был?\n"
            "Ваш Ответ: ");

            char *object_buffer = GetObject();
            if (CheckObjectExistance(Root, object_buffer) != NULL) {
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

                cur->value = GetObject();
            }

            break;
        }
        default:
            break;
        }

}

int main() {

    Menu("Base2.txt");

    return 0;
}
